/**************************************************************************/
/*  sspr_effect.cpp                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "sspr_effect.h"

#include "servers/rendering/renderer_rd/effects/copy_effects.h"
#include "servers/rendering/renderer_rd/effects/ss_effects.h"
#include "servers/rendering/renderer_rd/storage_rd/render_scene_buffers_rd.h"
#include "servers/rendering/renderer_rd/uniform_set_cache_rd.h"

using namespace RendererRD;

// Helper: store a Projection matrix as a column-major float[16]
static _FORCE_INLINE_ void store_camera(const Projection &p_mtx, float *p_array) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			p_array[i * 4 + j] = p_mtx.columns[i][j];
		}
	}
}

SSPREffect::SSPREffect() {
	// Initialize scatter shader
	{
		Vector<String> scatter_modes;
		scatter_modes.push_back("\n"); // Default
		scatter_shader.initialize(scatter_modes);
		scatter_shader_version = scatter_shader.version_create();
		scatter_pipeline.create_compute_pipeline(scatter_shader.version_get_shader(scatter_shader_version, 0));
	}

	// Initialize resolve shader
	{
		Vector<String> resolve_modes;
		resolve_modes.push_back("\n"); // Default
		resolve_shader.initialize(resolve_modes);
		resolve_shader_version = resolve_shader.version_create();
		resolve_pipeline.create_compute_pipeline(resolve_shader.version_get_shader(resolve_shader_version, 0));
	}

	// Initialize temporal shader
	{
		Vector<String> temporal_modes;
		temporal_modes.push_back("\n"); // Default
		temporal_shader.initialize(temporal_modes);
		temporal_shader_version = temporal_shader.version_create();
		temporal_pipeline.create_compute_pipeline(temporal_shader.version_get_shader(temporal_shader_version, 0));
	}

	// Initialize Dual Kawase Blur shaders
	{
		Vector<String> blur_modes;
		blur_modes.push_back("\n"); // Default
		blur_downscaling_shader.initialize(blur_modes);
		blur_downscaling_shader_version = blur_downscaling_shader.version_create();
		blur_downscaling_pipeline.create_compute_pipeline(blur_downscaling_shader.version_get_shader(blur_downscaling_shader_version, 0));

		blur_upscaling_shader.initialize(blur_modes);
		blur_upscaling_shader_version = blur_upscaling_shader.version_create();
		blur_upscaling_pipeline.create_compute_pipeline(blur_upscaling_shader.version_get_shader(blur_upscaling_shader_version, 0));
	}

	// Create samplers
	{
		nearest_sampler = RD::get_singleton()->sampler_create(RD::SamplerState());
		RD::SamplerState linear_state;
		linear_state.min_filter = RD::SAMPLER_FILTER_LINEAR;
		linear_state.mag_filter = RD::SAMPLER_FILTER_LINEAR;
		linear_state.mip_filter = RD::SAMPLER_FILTER_LINEAR;
		linear_sampler = RD::get_singleton()->sampler_create(linear_state);
	}
}

SSPREffect::~SSPREffect() {
	// Free pipelines
	scatter_pipeline.free();
	resolve_pipeline.free();
	temporal_pipeline.free();
	blur_downscaling_pipeline.free();
	blur_upscaling_pipeline.free();

	// Free shader versions
	scatter_shader.version_free(scatter_shader_version);
	resolve_shader.version_free(resolve_shader_version);
	temporal_shader.version_free(temporal_shader_version);
	blur_downscaling_shader.version_free(blur_downscaling_shader_version);
	blur_upscaling_shader.version_free(blur_upscaling_shader_version);

	// Free UBO
	if (scene_ubo.is_valid()) {
		RD::get_singleton()->free_rid(scene_ubo);
	}

	// Free samplers
	RD::get_singleton()->free_rid(nearest_sampler);
	RD::get_singleton()->free_rid(linear_sampler);

	// Free blur pyramid
	_free_blur_pyramid();
}

void SSPREffect::allocate_buffers(Ref<RenderSceneBuffersRD> p_render_buffers) {
	Size2i internal_size = p_render_buffers->get_internal_size();

	if (last_size == internal_size) {
		return;
	}

	uint32_t view_count = p_render_buffers->get_view_count();

	// Hash Map: R32_UINT + STORAGE_ATOMIC for imageAtomicMax
	p_render_buffers->create_texture(RB_SCOPE_SSPR, RB_SSPR_HASH_MAP,
			RD::DATA_FORMAT_R32_UINT,
			RD::TEXTURE_USAGE_SAMPLING_BIT | RD::TEXTURE_USAGE_STORAGE_BIT | RD::TEXTURE_USAGE_STORAGE_ATOMIC_BIT | RD::TEXTURE_USAGE_CAN_COPY_TO_BIT,
			RD::TEXTURE_SAMPLES_1, internal_size, view_count, 1, true);

	// Reflection output: R8G8B8A8_UNORM
	p_render_buffers->create_texture(RB_SCOPE_SSPR, RB_SSPR_REFLECTION,
			RD::DATA_FORMAT_R8G8B8A8_UNORM,
			RD::TEXTURE_USAGE_SAMPLING_BIT | RD::TEXTURE_USAGE_STORAGE_BIT | RD::TEXTURE_USAGE_CAN_COPY_FROM_BIT | RD::TEXTURE_USAGE_CAN_COPY_TO_BIT,
			RD::TEXTURE_SAMPLES_1, internal_size, view_count, 1, true);

	// History texture: R8G8B8A8_UNORM (for temporal pass)
	p_render_buffers->create_texture(RB_SCOPE_SSPR, RB_SSPR_HISTORY,
			RD::DATA_FORMAT_R8G8B8A8_UNORM,
			RD::TEXTURE_USAGE_SAMPLING_BIT | RD::TEXTURE_USAGE_STORAGE_BIT | RD::TEXTURE_USAGE_CAN_COPY_FROM_BIT | RD::TEXTURE_USAGE_CAN_COPY_TO_BIT,
			RD::TEXTURE_SAMPLES_1, internal_size, view_count, 1, true);

	// Blur temp texture: R8G8B8A8_UNORM (for gaussian blur / temporal output)
	p_render_buffers->create_texture(RB_SCOPE_SSPR, RB_SSPR_BLUR_TEMP,
			RD::DATA_FORMAT_R8G8B8A8_UNORM,
			RD::TEXTURE_USAGE_SAMPLING_BIT | RD::TEXTURE_USAGE_STORAGE_BIT | RD::TEXTURE_USAGE_CAN_COPY_FROM_BIT | RD::TEXTURE_USAGE_CAN_COPY_TO_BIT,
			RD::TEXTURE_SAMPLES_1, internal_size, view_count, 1, true);

	last_size = internal_size;
}

void SSPREffect::screen_space_planar_reflection(
		Ref<RenderSceneBuffersRD> p_render_buffers,
		RID p_color_texture,
		RID p_depth_texture,
		const Projection &p_projection,
		const Transform3D &p_cam_transform,
		float p_water_height,
		const Vector2 &p_jitter,
		CopyEffects &p_copy_effects,
		bool p_enable_temporal) {
	UniformSetCacheRD *uniform_set_cache = UniformSetCacheRD::get_singleton();
	ERR_FAIL_NULL(uniform_set_cache);

	Size2i internal_size = p_render_buffers->get_internal_size();

	// Allocate buffers if needed
	allocate_buffers(p_render_buffers);

	// ===================================================================
	// Update scene data UBO
	// ===================================================================
	{
		if (scene_ubo.is_null()) {
			scene_ubo = RD::get_singleton()->uniform_buffer_create(sizeof(SSPRSceneData));
		}

		SSPRSceneData scene_data;
		Projection correction;
		correction.set_depth_correction(true);

		// Build view-projection matrix: clip = projection * view * world
		// view = inverse of camera world transform
		Projection view_matrix = Projection(p_cam_transform.affine_inverse());
		Projection view_proj = correction * p_projection * view_matrix;
		store_camera(view_proj, scene_data.projection);
		store_camera(view_proj.inverse(), scene_data.inv_projection);
		store_camera(Projection(p_cam_transform), scene_data.cam_transform);

		// prev_projection: previous frame's view_proj for Temporal Pass reprojection.
		// First frame: identity (no history), subsequent frames: last frame's view_proj.
		if (first_frame) {
			float identity[16] = {
				1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
			};
			memcpy(scene_data.prev_projection, identity, sizeof(identity));
		} else {
			store_camera(last_view_proj, scene_data.prev_projection);
		}

		RD::get_singleton()->buffer_update(scene_ubo, 0, sizeof(SSPRSceneData), &scene_data);
	}

	// ===================================================================
	// Acquire textures from RenderSceneBuffersRD
	// ===================================================================
	RID hash_map_tex = p_render_buffers->get_texture(RB_SCOPE_SSPR, RB_SSPR_HASH_MAP);
	RID reflection_tex = p_render_buffers->get_texture(RB_SCOPE_SSPR, RB_SSPR_REFLECTION);
	RID history_tex = p_render_buffers->get_texture(RB_SCOPE_SSPR, RB_SSPR_HISTORY);

	// ===================================================================
	// Clear hash map to 0 (matching reference: rd.texture_clear)
	// ===================================================================
	RD::get_singleton()->texture_clear(hash_map_tex, Color(0, 0, 0, 0), 0, 1, 0, 1);

	// ===================================================================
	// Pass 1: Scatter
	// ===================================================================
	{
		RD::ComputeListID compute_list = RD::get_singleton()->compute_list_begin();
		RD::get_singleton()->draw_command_end_label(); // Begin SSPR Scatter

		RD::get_singleton()->compute_list_bind_compute_pipeline(compute_list, scatter_pipeline.get_rid());

		RD::Uniform u_depth(RD::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE, 0, Vector<RID>({ nearest_sampler, p_depth_texture }));
		RD::Uniform u_hash_map(RD::UNIFORM_TYPE_IMAGE, 1, Vector<RID>({ hash_map_tex }));
		RD::Uniform u_scene_data(RD::UNIFORM_TYPE_UNIFORM_BUFFER, 2, Vector<RID>({ scene_ubo }));

		RD::get_singleton()->compute_list_bind_uniform_set(compute_list,
				uniform_set_cache->get_cache(scatter_shader.version_get_shader(scatter_shader_version, 0), 0, u_depth, u_hash_map, u_scene_data), 0);

		SSPRScatterPushConstant scatter_pc;
		scatter_pc.screen_size[0] = internal_size.x;
		scatter_pc.screen_size[1] = internal_size.y;
		scatter_pc.water_height = p_water_height;
		scatter_pc.jitter_x = p_jitter.x;
		scatter_pc.jitter_y = p_jitter.y;
		scatter_pc.pad = 0;

		RD::get_singleton()->compute_list_set_push_constant(compute_list, &scatter_pc, sizeof(SSPRScatterPushConstant));
		RD::get_singleton()->compute_list_dispatch_threads(compute_list, internal_size.x, internal_size.y, 1);

		RD::get_singleton()->compute_list_end();
		RD::get_singleton()->draw_command_end_label(); // End SSPR Scatter
	}

	// ===================================================================
	// Pass 2: Resolve (separate compute list — hash_map is now read-only)
	// ===================================================================
	{
		RD::ComputeListID compute_list = RD::get_singleton()->compute_list_begin();
		RD::get_singleton()->draw_command_end_label(); // Begin SSPR Resolve

		RD::get_singleton()->compute_list_bind_compute_pipeline(compute_list, resolve_pipeline.get_rid());

		RD::Uniform u_color(RD::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE, 0, Vector<RID>({ linear_sampler, p_color_texture }));
		RD::Uniform u_hash_map(RD::UNIFORM_TYPE_IMAGE, 1, Vector<RID>({ hash_map_tex }));
		RD::Uniform u_reflection(RD::UNIFORM_TYPE_IMAGE, 2, Vector<RID>({ reflection_tex }));

		RD::get_singleton()->compute_list_bind_uniform_set(compute_list,
				uniform_set_cache->get_cache(resolve_shader.version_get_shader(resolve_shader_version, 0), 0,
						u_color, u_hash_map, u_reflection), 0);

		RD::get_singleton()->compute_list_dispatch_threads(compute_list, internal_size.x, internal_size.y, 1);

		RD::get_singleton()->compute_list_end();
		RD::get_singleton()->draw_command_end_label(); // End SSPR Resolve
	}

	// ===================================================================
	// Pass 3: Temporal (TAA accumulation — depth reprojection + neighbor clamp + exponential blend)
	// Mobile (p_enable_temporal=true): skip full temporal pass to save 1 compute dispatch
	// ===================================================================
	if (!p_enable_temporal) {
		RID blur_temp_tex = p_render_buffers->get_texture(RB_SCOPE_SSPR, RB_SSPR_BLUR_TEMP);

		if (first_frame) {
			// First frame: no history, just copy reflection to history for next frame
			RD::get_singleton()->texture_copy(reflection_tex, history_tex, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(internal_size.x, internal_size.y, 1), 0, 0, 0, 0);
		} else {
			RD::ComputeListID compute_list = RD::get_singleton()->compute_list_begin();
			RD::get_singleton()->draw_command_end_label(); // Begin SSPR Temporal

			RD::get_singleton()->compute_list_bind_compute_pipeline(compute_list, temporal_pipeline.get_rid());

			// Output to blur_temp (separate texture from samplers — avoids Vulkan "same texture as sampler+image" error)
			RD::Uniform u_current(RD::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE, 0, Vector<RID>({ linear_sampler, reflection_tex }));
			RD::Uniform u_history(RD::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE, 1, Vector<RID>({ linear_sampler, history_tex }));
			RD::Uniform u_depth(RD::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE, 2, Vector<RID>({ nearest_sampler, p_depth_texture }));
			RD::Uniform u_scene_data_temporal(RD::UNIFORM_TYPE_UNIFORM_BUFFER, 3, Vector<RID>({ scene_ubo }));
			RD::Uniform u_output(RD::UNIFORM_TYPE_IMAGE, 4, Vector<RID>({ blur_temp_tex }));

			RD::get_singleton()->compute_list_bind_uniform_set(compute_list,
					uniform_set_cache->get_cache(temporal_shader.version_get_shader(temporal_shader_version, 0), 0,
							u_current, u_history, u_depth, u_scene_data_temporal, u_output), 0);

			SSPRTemporalPushConstant temporal_pc;
			temporal_pc.blend = 0.02f; // 2% current, 98% history — heavy temporal accumulation
			temporal_pc.neighbor_clamp_radius = 1.0f;
			temporal_pc.pad0 = 0.0f;
			temporal_pc.pad1 = 0.0f;

			RD::get_singleton()->compute_list_set_push_constant(compute_list, &temporal_pc, sizeof(SSPRTemporalPushConstant));
			RD::get_singleton()->compute_list_dispatch_threads(compute_list, internal_size.x, internal_size.y, 1);

			RD::get_singleton()->compute_list_end();
			RD::get_singleton()->draw_command_end_label(); // End SSPR Temporal

			// Copy temporal result to reflection (for floor shader) and history (for next frame)
			RD::get_singleton()->texture_copy(blur_temp_tex, reflection_tex, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(internal_size.x, internal_size.y, 1), 0, 0, 0, 0);
			RD::get_singleton()->texture_copy(blur_temp_tex, history_tex, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(internal_size.x, internal_size.y, 1), 0, 0, 0, 0);
		}
	}

	// Update temporal state for next frame
	Projection view_proj = Projection();
	{
		Projection correction;
		correction.set_depth_correction(true);
		Projection view_matrix = Projection(p_cam_transform.affine_inverse());
		view_proj = correction * p_projection * view_matrix;
	}
	last_view_proj = view_proj;
	first_frame = false;

	// Pass 4: Dual Kawase Blur (smooth reflection)
	// Mobile (p_enable_temporal=true): skip blur to save compute dispatch
	// ===================================================================
	if (!p_enable_temporal) {
		RID blur_temp_tex = p_render_buffers->get_texture(RB_SCOPE_SSPR, RB_SSPR_BLUR_TEMP);
		_run_dual_kawase_blur_pass(reflection_tex, blur_temp_tex, internal_size);
		// Copy blur result back to reflection texture for floor shader sampling
		RD::get_singleton()->texture_copy(blur_temp_tex, reflection_tex, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(internal_size.x, internal_size.y, 1), 0, 0, 0, 0);
	}
}

// ===================================================================
// Dual Kawase Blur helpers
// ===================================================================

void SSPREffect::_free_blur_pyramid() {
	for (BlurPyramidLevel &level : blur_pyramid) {
		if (level.down_rid.is_valid()) {
			RD::get_singleton()->free_rid(level.down_rid);
		}
		if (level.up_rid.is_valid()) {
			RD::get_singleton()->free_rid(level.up_rid);
		}
	}
	blur_pyramid.clear();
	blur_pyramid_size = Size2i();
	blur_pyramid_iterations = 0;
}

void SSPREffect::_ensure_blur_pyramid(const Size2i &p_size) {
	if (blur_pyramid_size == p_size && blur_pyramid_iterations == blur_iterations && blur_pyramid.size() > 0) {
		return; // Already valid
	}

	_free_blur_pyramid();

	blur_pyramid_size = p_size;
	blur_pyramid_iterations = blur_iterations;

	Size2i current_size = p_size;

	for (int i = 0; i < blur_iterations; i++) {
		BlurPyramidLevel level;
		level.size = current_size;

		RD::TextureFormat tf;
		tf.format = RD::DATA_FORMAT_R8G8B8A8_UNORM;
		tf.width = MAX(current_size.x, 1);
		tf.height = MAX(current_size.y, 1);
		tf.usage_bits = RD::TEXTURE_USAGE_SAMPLING_BIT | RD::TEXTURE_USAGE_STORAGE_BIT | RD::TEXTURE_USAGE_CAN_COPY_FROM_BIT;

		RD::TextureView tv;
		level.down_rid = RD::get_singleton()->texture_create(tf, tv);
		level.up_rid = RD::get_singleton()->texture_create(tf, tv);

		blur_pyramid.push_back(level);

		current_size.x = MAX(current_size.x / 2, 1);
		current_size.y = MAX(current_size.y / 2, 1);
	}
}

void SSPREffect::_run_dual_kawase_blur_pass(RID p_source_tex, RID p_dest_tex, const Size2i &p_size) {
	UniformSetCacheRD *uniform_set_cache = UniformSetCacheRD::get_singleton();
	ERR_FAIL_NULL(uniform_set_cache);

	_ensure_blur_pyramid(p_size);

	if (blur_pyramid.size() == 0) {
		return;
	}

	// ---- Downscaling pass ----
	RID last_down_rid = p_source_tex;

	for (int i = 0; i < blur_iterations; i++) {
		BlurPyramidLevel &level = blur_pyramid[i];

		RD::ComputeListID compute_list = RD::get_singleton()->compute_list_begin();

		RD::get_singleton()->compute_list_bind_compute_pipeline(compute_list, blur_downscaling_pipeline.get_rid());

		RD::Uniform u_source(RD::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE, 0, Vector<RID>({ linear_sampler, last_down_rid }));
		RD::Uniform u_dest(RD::UNIFORM_TYPE_IMAGE, 1, Vector<RID>({ level.down_rid }));

		RD::get_singleton()->compute_list_bind_uniform_set(compute_list,
				uniform_set_cache->get_cache(blur_downscaling_shader.version_get_shader(blur_downscaling_shader_version, 0), 0,
						u_source, u_dest), 0);

		struct {
			int32_t dst_size[2];
			float offset;
			float pad;
		} pc;
		pc.dst_size[0] = level.size.x;
		pc.dst_size[1] = level.size.y;
		pc.offset = blur_radius;
		pc.pad = 0.0f;

		RD::get_singleton()->compute_list_set_push_constant(compute_list, &pc, sizeof(pc));
		RD::get_singleton()->compute_list_dispatch_threads(compute_list, level.size.x, level.size.y, 1);
		RD::get_singleton()->compute_list_end();

		last_down_rid = level.down_rid;
	}

	// ---- Upscaling pass ----
	if (blur_iterations <= 1) {
		// Single iteration: copy last downscaled result to destination
		RD::get_singleton()->texture_copy(last_down_rid, p_dest_tex, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(p_size.x, p_size.y, 1), 0, 0, 0, 0);
		return;
	}

	RID last_up_rid = blur_pyramid[blur_iterations - 1].down_rid;

	for (int i = blur_iterations - 2; i >= 0; i--) {
		BlurPyramidLevel &level = blur_pyramid[i];

		RD::ComputeListID compute_list = RD::get_singleton()->compute_list_begin();

		RD::get_singleton()->compute_list_bind_compute_pipeline(compute_list, blur_upscaling_pipeline.get_rid());

		RD::Uniform u_source(RD::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE, 0, Vector<RID>({ linear_sampler, last_up_rid }));
		RD::Uniform u_dest(RD::UNIFORM_TYPE_IMAGE, 1, Vector<RID>({ level.up_rid }));

		RD::get_singleton()->compute_list_bind_uniform_set(compute_list,
				uniform_set_cache->get_cache(blur_upscaling_shader.version_get_shader(blur_upscaling_shader_version, 0), 0,
						u_source, u_dest), 0);

		struct {
			int32_t dst_size[2];
			float offset;
			float pad;
		} pc;
		pc.dst_size[0] = level.size.x;
		pc.dst_size[1] = level.size.y;
		pc.offset = blur_radius;
		pc.pad = 0.0f;

		RD::get_singleton()->compute_list_set_push_constant(compute_list, &pc, sizeof(pc));
		RD::get_singleton()->compute_list_dispatch_threads(compute_list, level.size.x, level.size.y, 1);
		RD::get_singleton()->compute_list_end();

		last_up_rid = level.up_rid;
	}

	// Copy final upscaled result to destination
	RD::get_singleton()->texture_copy(last_up_rid, p_dest_tex, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(p_size.x, p_size.y, 1), 0, 0, 0, 0);
}
