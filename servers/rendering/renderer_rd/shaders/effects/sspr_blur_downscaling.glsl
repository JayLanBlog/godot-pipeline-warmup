#[compute]

#version 450

#VERSION_DEFINES

// Dual Kawase Blur — Downscaling Pass
// 4-corner weighted average + center x4, normalized by 1/8

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout(set = 0, binding = 0) uniform sampler2D source_texture;
layout(rgba8, set = 0, binding = 1) uniform restrict writeonly image2D dest_texture;

layout(push_constant, std430) uniform Params {
	ivec2 dst_size;
	float offset;
	float pad;
}
params;

#define UV ((gl_GlobalInvocationID.xy + vec2(0.5)) / vec2(params.dst_size))
#define OFFSET params.offset
#define HALF_TEXEL (0.5 / vec2(params.dst_size))

void main() {
	ivec2 id = ivec2(gl_GlobalInvocationID.xy);

	if (id.x >= params.dst_size.x || id.y >= params.dst_size.y) {
		return;
	}

	vec4 c = texture(source_texture, UV) * 4.0;
	c += texture(source_texture, UV + vec2(-OFFSET - 1.0, -OFFSET - 1.0) * HALF_TEXEL);
	c += texture(source_texture, UV + vec2(-OFFSET - 1.0,  OFFSET + 1.0) * HALF_TEXEL);
	c += texture(source_texture, UV + vec2( OFFSET + 1.0, -OFFSET - 1.0) * HALF_TEXEL);
	c += texture(source_texture, UV + vec2( OFFSET + 1.0,  OFFSET + 1.0) * HALF_TEXEL);

	imageStore(dest_texture, id, c * 0.125);
}
