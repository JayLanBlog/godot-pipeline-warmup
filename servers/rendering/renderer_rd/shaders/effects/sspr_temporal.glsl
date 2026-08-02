#[compute]

#version 450

#VERSION_DEFINES

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

// 0: Current frame reflection (Resolve output)
layout(set = 0, binding = 0) uniform sampler2D source_current;

// 1: Previous frame history
layout(set = 0, binding = 1) uniform sampler2D source_history;

// 2: Depth texture (for reprojection)
layout(set = 0, binding = 2) uniform sampler2D source_depth;

// 3: Scene Data UBO (projection / inv_projection / prev_projection)
layout(set = 0, binding = 3, std140) uniform SceneData {
	mat4 projection;
	mat4 inv_projection;
	mat4 prev_projection;
	mat4 cam_transform;
}
scene_data;

// 4: Output
layout(rgba8, set = 0, binding = 4) uniform restrict image2D dest_temporal;

layout(push_constant, std430) uniform Params {
	float blend;
	float neighbor_clamp_radius;
	float pad0;
	float pad1;
}
params;

// Depth reprojection: NDC → world space
vec3 ndc_to_world(vec2 uv, float depth) {
	vec4 ndc = vec4(uv * 2.0 - 1.0, depth, 1.0);
	vec4 world = scene_data.inv_projection * ndc;
	return world.xyz / world.w;
}

// Reproject: world space → previous frame UV
vec2 world_to_prev_uv(vec3 world_pos) {
	vec4 prev_clip = scene_data.prev_projection * vec4(world_pos, 1.0);
	vec2 prev_ndc = prev_clip.xy / prev_clip.w;
	return (prev_ndc + 1.0) * 0.5;
}

// Neighborhood clamping: prevent ghosting
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

	// Read current frame reflection
	vec4 current_color = texture(source_current, uv);
	float depth = texture(source_depth, uv).r;

	// Reverse-Z: skip sky pixels (no depth info for reprojection)
	if (depth <= 0.0) {
		imageStore(dest_temporal, id, current_color);
		return;
	}

	// 1. Depth → world space
	vec3 world_pos = ndc_to_world(uv, depth);

	// 2. World → previous frame UV
	vec2 prev_uv = world_to_prev_uv(world_pos);

	// 3. Sample history (fallback to current if out of bounds)
	vec4 history_color = current_color;
	if (prev_uv.x >= 0.0 && prev_uv.x <= 1.0 && prev_uv.y >= 0.0 && prev_uv.y <= 1.0) {
		history_color = texture(source_history, prev_uv);
	}

	// 4. Neighbor clamp to prevent ghosting
	vec4 clamped_history = neighbor_clamp(source_current, history_color, uv, pixel_size, params.neighbor_clamp_radius);

	// 5. Exponential blend: small blend = heavy history reliance
	vec4 final_color = mix(clamped_history, current_color, params.blend);

	imageStore(dest_temporal, id, final_color);
}
