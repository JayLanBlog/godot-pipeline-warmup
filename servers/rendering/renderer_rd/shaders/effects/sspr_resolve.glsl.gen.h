/**************************************************************************/
/*  sspr_resolve.glsl.gen.h                                               */
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

class SsprResolveShaderRD : public ShaderRD {
public:
	SsprResolveShaderRD() {
		static const char *_vertex_code = nullptr;
		static const char *_fragment_code = nullptr;
		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;


layout(set = 0, binding = 0) uniform sampler2D source_color;



layout(r32ui, set = 0, binding = 1) uniform restrict readonly uimage2D source_hash_map;


layout(rgba8, set = 0, binding = 2) uniform restrict image2D dest_reflection;


const ivec2 NEIGHBORS[9] = ivec2[](
	ivec2(0, 0), ivec2(1, 0), ivec2(0, 1), ivec2(-1, 0), ivec2(0, -1),
	ivec2(1, 1), ivec2(-1, 1), ivec2(-1, -1), ivec2(1, -1)
);

ivec2 decode_packed(uint packed) {
	return ivec2(
		int(packed & 0xFFFFu),
		int((packed >> 16) & 0xFFFFu)
	);
}

void main() {
	ivec2 id = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(dest_reflection);

	if (id.x >= size.x || id.y >= size.y) {
		return;
	}

	
	uint packed = imageLoad(source_hash_map, id).r;

	
	if (packed == 0u) {
		
		for (int i = 1; i < 9; i++) {
			ivec2 neighbor_id = id + NEIGHBORS[i];
			
			if (neighbor_id.x < 0 || neighbor_id.x >= size.x ||
				neighbor_id.y < 0 || neighbor_id.y >= size.y) {
				continue;
			}
			packed = imageLoad(source_hash_map, neighbor_id).r;
			if (packed != 0u) {
				break; 
			}
		}
	}

	
	if (packed == 0u) {
		imageStore(dest_reflection, id, vec4(0.0, 0.0, 0.0, 0.0));
		return;
	}

	
	ivec2 src = decode_packed(packed);
	vec2 src_uv = (vec2(src) + 0.5) / vec2(size);

	
	vec4 color = texture(source_color, src_uv);
	imageStore(dest_reflection, id, vec4(color.rgb, 1.0));
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, _compute_code, "SsprResolveShaderRD");
	}
};
