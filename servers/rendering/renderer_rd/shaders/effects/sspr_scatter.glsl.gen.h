/**************************************************************************/
/*  sspr_scatter.glsl.gen.h                                               */
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

class SsprScatterShaderRD : public ShaderRD {
public:
	SsprScatterShaderRD() {
		static const char *_vertex_code = nullptr;
		static const char *_fragment_code = nullptr;
		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;


layout(set = 0, binding = 0) uniform sampler2D source_depth;



layout(r32ui, set = 0, binding = 1) uniform restrict uimage2D dest_hash_map;


layout(set = 0, binding = 2, std140) uniform SceneData {
	mat4 projection;
	mat4 inv_projection;
	mat4 prev_projection;
	mat4 cam_transform;
}
scene_data;

layout(push_constant, std430) uniform Params {
	ivec2 screen_size;
	float water_height;
	float jitter_x;
	float jitter_y;
	int pad;
}
params;




vec3 world_pos_from_depth(vec2 uv, float depth) {
	vec4 clip_pos = vec4(uv * 2.0 - 1.0, depth, 1.0);
	vec4 world_pos = scene_data.inv_projection * clip_pos;
	return world_pos.xyz / world_pos.w;
}

void main() {
	ivec2 size = imageSize(dest_hash_map);
	ivec2 id = ivec2(gl_GlobalInvocationID.xy);
	if (id.x >= size.x || id.y >= size.y) {
		return;
	}

	vec2 uv = (vec2(id) + 0.5) / vec2(size);
	float depth = texture(source_depth, uv).r;

	
	if (depth <= 0.0) {
		return;
	}

	
	vec3 world_pos = world_pos_from_depth(uv, depth);

	
	if (world_pos.y < params.water_height) {
		return;
	}

	
	vec3 reflected = world_pos;
	reflected.y = 2.0 * params.water_height - reflected.y;

	
	vec4 clip_pos = scene_data.projection * vec4(reflected, 1.0);
	vec3 ndc = clip_pos.xyz / clip_pos.w;

	
	vec2 reflected_uv = ndc.xy * 0.5 + 0.5;

	
	if (reflected_uv.x < 0.0 || reflected_uv.x > 1.0 || reflected_uv.y < 0.0 || reflected_uv.y > 1.0) {
		return;
	}

	
	ivec2 dest_coord = clamp(ivec2(reflected_uv * vec2(size)), ivec2(0), size - 1);
	uint packed = (uint(id.y) << 16) | (uint(id.x) & 0xFFFFu);
	imageAtomicMax(dest_hash_map, dest_coord, packed);
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, _compute_code, "SsprScatterShaderRD");
	}
};
