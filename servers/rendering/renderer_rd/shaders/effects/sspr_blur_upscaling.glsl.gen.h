/**************************************************************************/
/*  sspr_blur_upscaling.glsl.gen.h                                        */
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

class SsprBlurUpscalingShaderRD : public ShaderRD {
public:
	SsprBlurUpscalingShaderRD() {
		static const char *_vertex_code = nullptr;
		static const char *_fragment_code = nullptr;
		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES




layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout(set = 0, binding = 0) uniform sampler2D source_texture;
layout(rgba8, set = 0, binding = 1) uniform restrict writeonly image2D dest_texture;

layout(push_constant, std430) uniform Params {
	ivec2 dst_size;
	float offset;
	float pad;
}
params;

#define UV (vec2(gl_GlobalInvocationID.xy) / vec2(params.dst_size))
#define OFFSET params.offset
#define HALF_TEXEL (0.5 / vec2(params.dst_size))

void main() {
	ivec2 id = ivec2(gl_GlobalInvocationID.xy);

	if (id.x >= params.dst_size.x || id.y >= params.dst_size.y) {
		return;
	}

	vec4 sum = vec4(0.0);

	
	sum += texture(source_texture, UV + vec2( HALF_TEXEL.x,  HALF_TEXEL.y) * OFFSET) * 2.0;
	sum += texture(source_texture, UV + vec2(-HALF_TEXEL.x,  HALF_TEXEL.y) * OFFSET) * 2.0;
	sum += texture(source_texture, UV + vec2( HALF_TEXEL.x, -HALF_TEXEL.y) * OFFSET) * 2.0;
	sum += texture(source_texture, UV + vec2(-HALF_TEXEL.x, -HALF_TEXEL.y) * OFFSET) * 2.0;

	
	sum += texture(source_texture, UV + vec2( HALF_TEXEL.x * 2.0, 0.0) * OFFSET);
	sum += texture(source_texture, UV + vec2(-HALF_TEXEL.x * 2.0, 0.0) * OFFSET);
	sum += texture(source_texture, UV + vec2(0.0,  HALF_TEXEL.y * 2.0) * OFFSET);
	sum += texture(source_texture, UV + vec2(0.0, -HALF_TEXEL.y * 2.0) * OFFSET);

	imageStore(dest_texture, id, sum * 0.0833);
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, _compute_code, "SsprBlurUpscalingShaderRD");
	}
};
