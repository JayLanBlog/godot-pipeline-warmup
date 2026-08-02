/**************************************************************************/
/*  sspr_effect.h                                                         */
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

#pragma once

#include "servers/rendering/renderer_rd/pipeline_deferred_rd.h"
#include "servers/rendering/renderer_rd/shaders/effects/sspr_scatter.glsl.gen.h"
#include "servers/rendering/renderer_rd/shaders/effects/sspr_resolve.glsl.gen.h"
#include "servers/rendering/renderer_rd/shaders/effects/sspr_temporal.glsl.gen.h"
#include "servers/rendering/renderer_rd/shaders/effects/sspr_blur_downscaling.glsl.gen.h"
#include "servers/rendering/renderer_rd/shaders/effects/sspr_blur_upscaling.glsl.gen.h"

class RenderSceneBuffersRD;

namespace RendererRD {

class CopyEffects;

// Screen Space Planar Reflection — SSPRSceneData (UBO, std140)
struct SSPRSceneData {
	float projection[16];          // view_proj matrix (column-major)
	float inv_projection[16];      // inv_view_proj for depth→world reconstruction
	float prev_projection[16];     // prev_view_proj for temporal reprojection (Mobile)
	float cam_transform[16];       // camera world transform (reserved)
};

// Push Constant for Scatter Pass
struct SSPRScatterPushConstant {
	int32_t screen_size[2];
	float water_height;
	float jitter_x;
	float jitter_y;
	int32_t pad;
};

// Push Constant for Resolve Pass
struct SSPRResolvePushConstant {
	int32_t screen_size[2];
	int32_t neighbor_search_radius;
	float edge_fade;
	int32_t enable_temporal;
	float pad;
};

// Push Constant for Temporal Pass
struct SSPRTemporalPushConstant {
	float blend;
	float neighbor_clamp_radius;
	float pad0;
	float pad1;
};

class SSPREffect {
public:
	SSPREffect();
	~SSPREffect();

	// Allocate render buffers through RenderSceneBuffersRD
	void allocate_buffers(Ref<RenderSceneBuffersRD> p_render_buffers);

	// Main entry: Scatter → Resolve → (optional Blur)
	void screen_space_planar_reflection(
			Ref<RenderSceneBuffersRD> p_render_buffers,
			RID p_color_texture,
			RID p_depth_texture,
			const Projection &p_projection,
			const Transform3D &p_cam_transform,
			float p_water_height,
			const Vector2 &p_jitter,
			CopyEffects &p_copy_effects,
			bool p_enable_temporal);

private:
	// Shaders & Pipelines
	SsprScatterShaderRD scatter_shader;
	RID scatter_shader_version;
	PipelineDeferredRD scatter_pipeline;

	SsprResolveShaderRD resolve_shader;
	RID resolve_shader_version;
	PipelineDeferredRD resolve_pipeline;

	SsprTemporalShaderRD temporal_shader;
	RID temporal_shader_version;
	PipelineDeferredRD temporal_pipeline;

	// Scene data UBO
	RID scene_ubo;

	// Samplers
	RID nearest_sampler;
	RID linear_sampler;

	// Cached buffer size for resize detection
	Size2i last_size;

	// Temporal state
	Projection last_view_proj;
	bool first_frame = true;

	// Dual Kawase Blur
	static constexpr int MAX_BLUR_ITERATIONS = 8;

	struct BlurPyramidLevel {
		RID down_rid; // downscaled result (storage for next level or upscaling source)
		RID up_rid; // upscaled result (final output for this level)
		Size2i size; // dimensions of this level
	};

	int blur_iterations = 4;
	float blur_radius = 0.5f;
	LocalVector<BlurPyramidLevel> blur_pyramid;
	Size2i blur_pyramid_size; // cached size for rebuild detection
	int blur_pyramid_iterations = 0; // cached iteration count

	SsprBlurDownscalingShaderRD blur_downscaling_shader;
	RID blur_downscaling_shader_version;
	PipelineDeferredRD blur_downscaling_pipeline;

	SsprBlurUpscalingShaderRD blur_upscaling_shader;
	RID blur_upscaling_shader_version;
	PipelineDeferredRD blur_upscaling_pipeline;

	void _free_blur_pyramid();
	void _ensure_blur_pyramid(const Size2i &p_size);
	void _run_dual_kawase_blur_pass(RID p_source_tex, RID p_dest_tex, const Size2i &p_size);
};

} // namespace RendererRD
