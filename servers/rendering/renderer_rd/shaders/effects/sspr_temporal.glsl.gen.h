/**************************************************************************/
/*  sspr_temporal.glsl.gen.h                                              */
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

/* THIS FILE IS GENERATED. EDITS WILL BE LOST. */

#pragma once

#include "servers/rendering/renderer_rd/shader_rd.h"

class SsprTemporalShaderRD : public ShaderRD {
public:
	SsprTemporalShaderRD() {
		static const char *_vertex_code = nullptr;
		static const char *_fragment_code = nullptr;
		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;


layout(set = 0, binding = 0) uniform sampler2D source_current;


layout(set = 0, binding = 1) uniform sampler2D source_history;


layout(set = 0, binding = 2) uniform sampler2D source_depth;


layout(set = 0, binding = 3, std140) uniform SceneData {
	mat4 projection;
	mat4 inv_projection;
	mat4 prev_projection;
	mat4 cam_transform;
}
scene_data;


layout(rgba8, set = 0, binding = 4) uniform restrict image2D dest_temporal;

layout(push_constant, std430) uniform Params {
	float blend;
	float neighbor_clamp_radius;
	float pad0;
	float pad1;
}
params;


vec3 ndc_to_world(vec2 uv, float depth) {
	vec4 ndc = vec4(uv * 2.0 - 1.0, depth, 1.0);
	vec4 world = scene_data.inv_projection * ndc;
	return world.xyz / world.w;
}


vec2 world_to_prev_uv(vec3 world_pos) {
	vec4 prev_clip = scene_data.prev_projection * vec4(world_pos, 1.0);
	vec2 prev_ndc = prev_clip.xy / prev_clip.w;
	return (prev_ndc + 1.0) * 0.5;
}


vec4 neighbor_clamp(sampler2D current_tex, vec4 history_color, vec2 uv, vec2 pixel_size, float radius) {
	vec2 offsets[5] = vec2[](
		vec2(0.0, 0.0),
		vec2(-radius, 0.0), vec2(radius, 0.0),
		vec2(0.0, -radius), vec2(0.0, radius)
	);

	vec4 min_color = vec4(1e3);
	vec4 max_color = vec4(-1e3);

	for (int i = 0; i < 5; i++) {
		vec4 sample_color = texture(current_tex, uv + offsets[i] * pixel_size);
		min_color = min(min_color, sample_color);
		max_color = max(max_color, sample_color);
	}

	return clamp(history_color, min_color, max_color);
}

void main() {
	ivec2 id = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(dest_temporal);

	if (id.x >= size.x || id.y >= size.y) {
		return;
	}

	vec2 uv = (vec2(id) + 0.5) / vec2(size);
	vec2 pixel_size = 1.0 / vec2(size);

	
	vec4 current_color = texture(source_current, uv);
	float depth = texture(source_depth, uv).r;

	
	if (depth <= 0.0) {
		imageStore(dest_temporal, id, current_color);
		return;
	}

	
	vec3 world_pos = ndc_to_world(uv, depth);

	
	vec2 prev_uv = world_to_prev_uv(world_pos);

	
	vec4 history_color = current_color;
	if (prev_uv.x >= 0.0 && prev_uv.x <= 1.0 && prev_uv.y >= 0.0 && prev_uv.y <= 1.0) {
		history_color = texture(source_history, prev_uv);
	}

	
	vec4 clamped_history = neighbor_clamp(source_current, history_color, uv, pixel_size, params.neighbor_clamp_radius);

	
	vec4 final_color = mix(clamped_history, current_color, params.blend);

	imageStore(dest_temporal, id, final_color);
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, _compute_code, "SsprTemporalShaderRD");
	}
};
