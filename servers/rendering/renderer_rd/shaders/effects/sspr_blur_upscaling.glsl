#[compute]

#version 450

#VERSION_DEFINES

// Dual Kawase Blur — Upscaling Pass
// 8-direction weighted average: 4 corners x2 + 4 edges x1, normalized by 1/12

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

	// 4 corners (×2 weight)
	sum += texture(source_texture, UV + vec2( HALF_TEXEL.x,  HALF_TEXEL.y) * OFFSET) * 2.0;
	sum += texture(source_texture, UV + vec2(-HALF_TEXEL.x,  HALF_TEXEL.y) * OFFSET) * 2.0;
	sum += texture(source_texture, UV + vec2( HALF_TEXEL.x, -HALF_TEXEL.y) * OFFSET) * 2.0;
	sum += texture(source_texture, UV + vec2(-HALF_TEXEL.x, -HALF_TEXEL.y) * OFFSET) * 2.0;

	// 4 edges (×1 weight)
	sum += texture(source_texture, UV + vec2( HALF_TEXEL.x * 2.0, 0.0) * OFFSET);
	sum += texture(source_texture, UV + vec2(-HALF_TEXEL.x * 2.0, 0.0) * OFFSET);
	sum += texture(source_texture, UV + vec2(0.0,  HALF_TEXEL.y * 2.0) * OFFSET);
	sum += texture(source_texture, UV + vec2(0.0, -HALF_TEXEL.y * 2.0) * OFFSET);

	imageStore(dest_texture, id, sum * 0.0833);
}
