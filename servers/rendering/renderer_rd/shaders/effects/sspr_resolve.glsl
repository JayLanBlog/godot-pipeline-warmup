#[compute]

#version 450

#VERSION_DEFINES

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

// 0: Source scene color (current frame)
layout(set = 0, binding = 0) uniform sampler2D source_color;

// 1: Hash Map (R32_UINT, from Scatter pass)
// Packed: High 16 bits = Source Y, Low 16 bits = Source X
layout(r32ui, set = 0, binding = 1) uniform restrict readonly uimage2D source_hash_map;

// 2: Output reflection texture
layout(rgba8, set = 0, binding = 2) uniform restrict image2D dest_reflection;

// Neighbor search offsets (3x3 kernel, spiral order)
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

	// Read hash map: packed source pixel coordinates
	uint packed = imageLoad(source_hash_map, id).r;

	// If no data at this pixel, search neighbors for a valid pixel
	if (packed == 0u) {
		// Search 3x3 neighborhood
		for (int i = 1; i < 9; i++) {
			ivec2 neighbor_id = id + NEIGHBORS[i];
			// Bounds check
			if (neighbor_id.x < 0 || neighbor_id.x >= size.x ||
				neighbor_id.y < 0 || neighbor_id.y >= size.y) {
				continue;
			}
			packed = imageLoad(source_hash_map, neighbor_id).r;
			if (packed != 0u) {
				break; // Found a valid neighbor
			}
		}
	}

	// Still no data after neighbor search
	if (packed == 0u) {
		imageStore(dest_reflection, id, vec4(0.0, 0.0, 0.0, 0.0));
		return;
	}

	// Decode source coordinates
	ivec2 src = decode_packed(packed);
	vec2 src_uv = (vec2(src) + 0.5) / vec2(size);

	// Sample source color at the reflected position
	vec4 color = texture(source_color, src_uv);
	imageStore(dest_reflection, id, vec4(color.rgb, 1.0));
}