#[compute]

#version 450

#VERSION_DEFINES

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

// 0: Depth texture (source depth buffer)
layout(set = 0, binding = 0) uniform sampler2D source_depth;

// 1: Hash Map (R32_UINT, atomic read/write)
// Packed format: High 16 bits = Source Y, Low 16 bits = Source X
layout(r32ui, set = 0, binding = 1) uniform restrict uimage2D dest_hash_map;

// 2: Scene Data UBO (projection matrices)
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

// Reconstruct WORLD space position from depth
// inv_projection is inverse of the FULL view-projection matrix,
// so the result is already in world space (not view space).
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

	// Reverse-Z: depth=0.0 is far plane (sky), depth=1.0 is near plane
	if (depth <= 0.0) {
		return;
	}

	// Reconstruct world space position from depth
	vec3 world_pos = world_pos_from_depth(uv, depth);

	// Only reflect points above the water plane
	if (world_pos.y < params.water_height) {
		return;
	}

	// Reflect Y across water plane
	vec3 reflected = world_pos;
	reflected.y = 2.0 * params.water_height - reflected.y;

	// Project back to clip space using full view-projection matrix
	vec4 clip_pos = scene_data.projection * vec4(reflected, 1.0);
	vec3 ndc = clip_pos.xyz / clip_pos.w;

	// Convert to NDC UV
	vec2 reflected_uv = ndc.xy * 0.5 + 0.5;

	// Check if within screen bounds
	if (reflected_uv.x < 0.0 || reflected_uv.x > 1.0 || reflected_uv.y < 0.0 || reflected_uv.y > 1.0) {
		return;
	}

	// Clamp destination to valid range
	ivec2 dest_coord = clamp(ivec2(reflected_uv * vec2(size)), ivec2(0), size - 1);
	uint packed = (uint(id.y) << 16) | (uint(id.x) & 0xFFFFu);
	imageAtomicMax(dest_hash_map, dest_coord, packed);
}