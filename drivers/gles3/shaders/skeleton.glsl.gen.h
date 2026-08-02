/**************************************************************************/
/*  skeleton.glsl.gen.h                                                   */
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

#include "drivers/gles3/shader_gles3.h"

class SkeletonShaderGLES3 : public ShaderGLES3 {
public:
	enum Uniforms {
		BLEND_WEIGHT,
		BLEND_SHAPE_COUNT,
		SKELETON_TRANSFORM_X,
		SKELETON_TRANSFORM_Y,
		SKELETON_TRANSFORM_OFFSET,
		INVERSE_TRANSFORM_X,
		INVERSE_TRANSFORM_Y,
		INVERSE_TRANSFORM_OFFSET,
	};

	enum ShaderVariant {
		MODE_BASE_PASS,
		MODE_BLEND_PASS,
	};

	enum Specializations {
		MODE_2D = 1,
		USE_BLEND_SHAPES = 2,
		USE_SKELETON = 4,
		USE_NORMAL = 8,
		USE_TANGENT = 16,
		FINAL_PASS = 32,
		USE_EIGHT_WEIGHTS = 64,
	};

	_FORCE_INLINE_ bool version_bind_shader(RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		return _version_bind_shader(p_version, p_variant, p_specialization);
	}

	_FORCE_INLINE_ int version_get_uniform(Uniforms p_uniform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		return _version_get_uniform(p_uniform, p_version, p_variant, p_specialization);
	}

	/* clang-format off */
#define TRY_GET_UNIFORM(var_name) int var_name = version_get_uniform(p_uniform, p_version, p_variant, p_specialization); if (var_name < 0) return
	/* clang-format on */

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1f(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, double p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1f(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint8_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int8_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint16_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int16_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint32_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int32_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Color &p_color, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat col[4] = { p_color.r, p_color.g, p_color.b, p_color.a };
		glUniform4fv(uniform_location, 1, col);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector2 &p_vec2, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec2[2] = { float(p_vec2.x), float(p_vec2.y) };
		glUniform2fv(uniform_location, 1, vec2);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Size2i &p_vec2, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		GLint vec2[2] = { GLint(p_vec2.x), GLint(p_vec2.y) };
		glUniform2iv(uniform_location, 1, vec2);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector3 &p_vec3, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec3[3] = { float(p_vec3.x), float(p_vec3.y), float(p_vec3.z) };
		glUniform3fv(uniform_location, 1, vec3);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector4 &p_vec4, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec4[4] = { float(p_vec4.x), float(p_vec4.y), float(p_vec4.z), float(p_vec4.w) };
		glUniform4fv(uniform_location, 1, vec4);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform2f(uniform_location, p_a, p_b);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, float p_c, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform3f(uniform_location, p_a, p_b, p_c);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, float p_c, float p_d, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform4f(uniform_location, p_a, p_b, p_c, p_d);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Transform3D &p_transform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		const Transform3D &tr = p_transform;

		GLfloat matrix[16] = { /* build a 16x16 matrix */
			(GLfloat)tr.basis.rows[0][0],
			(GLfloat)tr.basis.rows[1][0],
			(GLfloat)tr.basis.rows[2][0],
			(GLfloat)0,
			(GLfloat)tr.basis.rows[0][1],
			(GLfloat)tr.basis.rows[1][1],
			(GLfloat)tr.basis.rows[2][1],
			(GLfloat)0,
			(GLfloat)tr.basis.rows[0][2],
			(GLfloat)tr.basis.rows[1][2],
			(GLfloat)tr.basis.rows[2][2],
			(GLfloat)0,
			(GLfloat)tr.origin.x,
			(GLfloat)tr.origin.y,
			(GLfloat)tr.origin.z,
			(GLfloat)1
		};

		glUniformMatrix4fv(uniform_location, 1, false, matrix);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Transform2D &p_transform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		const Transform2D &tr = p_transform;

		GLfloat matrix[16] = { /* build a 16x16 matrix */
			(GLfloat)tr.columns[0][0],
			(GLfloat)tr.columns[0][1],
			(GLfloat)0,
			(GLfloat)0,
			(GLfloat)tr.columns[1][0],
			(GLfloat)tr.columns[1][1],
			(GLfloat)0,
			(GLfloat)0,
			(GLfloat)0,
			(GLfloat)0,
			(GLfloat)1,
			(GLfloat)0,
			(GLfloat)tr.columns[2][0],
			(GLfloat)tr.columns[2][1],
			(GLfloat)0,
			(GLfloat)1
		};

		glUniformMatrix4fv(uniform_location, 1, false, matrix);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Projection &p_matrix, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 1) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat matrix[16];

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				matrix[i * 4 + j] = p_matrix.columns[i][j];
			}
		}

		glUniformMatrix4fv(uniform_location, 1, false, matrix);
	}

#undef TRY_GET_UNIFORM

protected:
	virtual void _init() override {
		static const char *_uniform_strings[] = {
			"blend_weight",
			"blend_shape_count",
			"skeleton_transform_x",
			"skeleton_transform_y",
			"skeleton_transform_offset",
			"inverse_transform_x",
			"inverse_transform_y",
			"inverse_transform_offset"
		};
		static const char *_variant_defines[] = {
			"",
			"#define MODE_BLEND_PASS",
		};
		static TexUnitPair _texunit_pairs[] = {
			{ "skeleton_texture", 0 },
		};
		static UBOPair *_ubo_pairs = nullptr;
		static Specialization _spec_pairs[] = {
			{ "MODE_2D", true },
			{ "USE_BLEND_SHAPES", false },
			{ "USE_SKELETON", false },
			{ "USE_NORMAL", false },
			{ "USE_TANGENT", false },
			{ "FINAL_PASS", false },
			{ "USE_EIGHT_WEIGHTS", false },
		};
		static const Feedback _feedbacks[] = {
			{ "out_vertex", 0 },
			{ "out_normal", 8 },
			{ "out_tangent", 16 },
		};
		static const char _vertex_code[] = {
R"<!>(
// Compatibility renames. These are exposed with the "godot_" prefix
// to work around two distinct Adreno bugs:
// 1. Some Adreno devices expose ES310 functions in ES300 shaders.
//    Internally, we must use the "godot_" prefix, but user shaders
//    will be mapped automatically.
// 2. Adreno 3XX devices have poor implementations of the other packing
//    functions, so we just use our own there to keep it simple.

#ifdef USE_HALF2FLOAT
// Floating point pack/unpack functions are part of the GLSL ES 300 specification used by web and mobile.
// It appears to be safe to expose these on mobile, but when running through ANGLE this appears to break.
uint float2half(uint f) {
	uint e = f & uint(0x7f800000);
	if (e <= uint(0x38000000)) {
		return uint(0);
	} else {
		return ((f >> uint(16)) & uint(0x8000)) |
				(((e - uint(0x38000000)) >> uint(13)) & uint(0x7c00)) |
				((f >> uint(13)) & uint(0x03ff));
	}
}

uint half2float(uint h) {
	uint h_e = h & uint(0x7c00);
	return ((h & uint(0x8000)) << uint(16)) | uint((h_e >> uint(10)) != uint(0)) * (((h_e + uint(0x1c000)) << uint(13)) | ((h & uint(0x03ff)) << uint(13)));
}

uint godot_packHalf2x16(vec2 v) {
	return float2half(floatBitsToUint(v.x)) | float2half(floatBitsToUint(v.y)) << uint(16);
}

vec2 godot_unpackHalf2x16(uint v) {
	return vec2(uintBitsToFloat(half2float(v & uint(0xffff))),
			uintBitsToFloat(half2float(v >> uint(16))));
}

uint godot_packUnorm2x16(vec2 v) {
	uvec2 uv = uvec2(round(clamp(v, vec2(0.0), vec2(1.0)) * 65535.0));
	return uv.x | uv.y << uint(16);
}

vec2 godot_unpackUnorm2x16(uint p) {
	return vec2(float(p & uint(0xffff)), float(p >> uint(16))) * 0.000015259021; // 1.0 / 65535.0 optimization
}

uint godot_packSnorm2x16(vec2 v) {
	uvec2 uv = uvec2(round(clamp(v, vec2(-1.0), vec2(1.0)) * 32767.0) + 32767.0);
	return uv.x | uv.y << uint(16);
}

vec2 godot_unpackSnorm2x16(uint p) {
	vec2 v = vec2(float(p & uint(0xffff)), float(p >> uint(16)));
	return clamp((v - 32767.0) * vec2(0.00003051851), vec2(-1.0), vec2(1.0));
}

#define packHalf2x16 godot_packHalf2x16
#define unpackHalf2x16 godot_unpackHalf2x16
#define packUnorm2x16 godot_packUnorm2x16
#define unpackUnorm2x16 godot_unpackUnorm2x16
#define packSnorm2x16 godot_packSnorm2x16
#define unpackSnorm2x16 godot_unpackSnorm2x16

#endif // USE_HALF2FLOAT

// Always expose these as they are ES310 functions and not available in ES300 or GLSL 330.

uint godot_packUnorm4x8(vec4 v) {
	uvec4 uv = uvec4(round(clamp(v, vec4(0.0), vec4(1.0)) * 255.0));
	return uv.x | (uv.y << uint(8)) | (uv.z << uint(16)) | (uv.w << uint(24));
}

vec4 godot_unpackUnorm4x8(uint p) {
	return vec4(float(p & uint(0xff)), float((p >> uint(8)) & uint(0xff)), float((p >> uint(16)) & uint(0xff)), float(p >> uint(24))) * 0.00392156862; // 1.0 / 255.0
}

uint godot_packSnorm4x8(vec4 v) {
	uvec4 uv = uvec4(round(clamp(v, vec4(-1.0), vec4(1.0)) * 127.0) + 127.0);
	return uv.x | uv.y << uint(8) | uv.z << uint(16) | uv.w << uint(24);
}

vec4 godot_unpackSnorm4x8(uint p) {
	vec4 v = vec4(float(p & uint(0xff)), float((p >> uint(8)) & uint(0xff)), float((p >> uint(16)) & uint(0xff)), float(p >> uint(24)));
	return clamp((v - vec4(127.0)) * vec4(0.00787401574), vec4(-1.0), vec4(1.0));
}

#define packUnorm4x8 godot_packUnorm4x8
#define unpackUnorm4x8 godot_unpackUnorm4x8
#define packSnorm4x8 godot_packSnorm4x8
#define unpackSnorm4x8 godot_unpackSnorm4x8

#ifdef MODE_2D
#define VFORMAT vec2
#else
#define VFORMAT vec3
#endif

#ifdef FINAL_PASS
#define OFORMAT vec2
#else
#define OFORMAT uvec2
#endif

// These come from the source mesh and the output from previous passes.
layout(location = 0) in highp VFORMAT in_vertex;
#ifdef MODE_BLEND_PASS
#ifdef USE_NORMAL
layout(location = 1) in highp uvec2 in_normal;
#endif
#ifdef USE_TANGENT
layout(location = 2) in highp uvec2 in_tangent;
#endif
#else // MODE_BLEND_PASS
#ifdef USE_NORMAL
layout(location = 1) in highp vec2 in_normal;
#endif
#ifdef USE_TANGENT
layout(location = 2) in highp vec2 in_tangent;
#endif
#endif // MODE_BLEND_PASS

#ifdef USE_SKELETON
#ifdef USE_EIGHT_WEIGHTS
layout(location = 10) in highp uvec4 in_bone_attrib;
layout(location = 11) in highp uvec4 in_bone_attrib2;
layout(location = 12) in mediump vec4 in_weight_attrib;
layout(location = 13) in mediump vec4 in_weight_attrib2;
#else
layout(location = 10) in highp uvec4 in_bone_attrib;
layout(location = 11) in mediump vec4 in_weight_attrib;
#endif

uniform highp sampler2D skeleton_texture; // texunit:0
#endif

/* clang-format on */
#ifdef MODE_BLEND_PASS
layout(location = 3) in highp VFORMAT blend_vertex;
#ifdef USE_NORMAL
layout(location = 4) in highp vec2 blend_normal;
#endif
#ifdef USE_TANGENT
layout(location = 5) in highp vec2 blend_tangent;
#endif
#endif // MODE_BLEND_PASS

out highp VFORMAT out_vertex; //tfb:

#ifdef USE_NORMAL
flat out highp OFORMAT out_normal; //tfb:USE_NORMAL
#endif
#ifdef USE_TANGENT
flat out highp OFORMAT out_tangent; //tfb:USE_TANGENT
#endif

#ifdef USE_BLEND_SHAPES
uniform highp float blend_weight;
uniform lowp float blend_shape_count;
#endif

#ifdef USE_SKELETON
uniform mediump vec2 skeleton_transform_x;
uniform mediump vec2 skeleton_transform_y;
uniform mediump vec2 skeleton_transform_offset;

uniform mediump vec2 inverse_transform_x;
uniform mediump vec2 inverse_transform_y;
uniform mediump vec2 inverse_transform_offset;
#endif

vec2 signNotZero(vec2 v) {
	return mix(vec2(-1.0), vec2(1.0), greaterThanEqual(v.xy, vec2(0.0)));
}

vec3 oct_to_vec3(vec2 oct) {
	oct = oct * 2.0 - 1.0;
	vec3 v = vec3(oct.xy, 1.0 - abs(oct.x) - abs(oct.y));
	if (v.z < 0.0) {
		v.xy = (1.0 - abs(v.yx)) * signNotZero(v.xy);
	}
	return normalize(v);
}

vec2 vec3_to_oct(vec3 e) {
	e /= abs(e.x) + abs(e.y) + abs(e.z);
	vec2 oct = e.z >= 0.0f ? e.xy : (vec2(1.0f) - abs(e.yx)) * signNotZero(e.xy);
	return oct * 0.5f + 0.5f;
}

vec4 oct_to_tang(vec2 oct_sign_encoded) {
	// Binormal sign encoded in y component
	vec2 oct = vec2(oct_sign_encoded.x, abs(oct_sign_encoded.y) * 2.0 - 1.0);
	return vec4(oct_to_vec3(oct), sign(oct_sign_encoded.y));
}

vec2 tang_to_oct(vec4 base) {
	vec2 oct = vec3_to_oct(base.xyz);
	// Encode binormal sign in y component
	oct.y = oct.y * 0.5f + 0.5f;
	oct.y = base.w >= 0.0f ? oct.y : 1.0 - oct.y;
	return oct;
}

// Our original input for normals and tangents is 2 16-bit floats.
// Transform Feedback has to write out 32-bits per channel.
// Octahedral compression requires normalized vectors, but we need to store
// non-normalized vectors until the very end.
// Therefore, we will compress our normals into 16 bits using signed-normalized
// fixed point precision. This works well, because we know that each normal
// is no larger than |1| so we can normalize by dividing by the number of blend
// shapes.
uvec2 vec4_to_vec2(vec4 p_vec) {
	return uvec2(packSnorm2x16(p_vec.xy), packSnorm2x16(p_vec.zw));
}

vec4 vec2_to_vec4(uvec2 p_vec) {
	return vec4(unpackSnorm2x16(p_vec.x), unpackSnorm2x16(p_vec.y));
}

void main() {
#ifdef MODE_2D
	out_vertex = in_vertex;

#ifdef USE_BLEND_SHAPES
#ifdef MODE_BLEND_PASS
	out_vertex = in_vertex + blend_vertex * blend_weight;
#else
	out_vertex = in_vertex * blend_weight;
#endif
#ifdef FINAL_PASS
	out_vertex = normalize(out_vertex);
#endif
#endif // USE_BLEND_SHAPES

#ifdef USE_SKELETON

#define TEX(m) texelFetch(skeleton_texture, ivec2(m % 256u, m / 256u), 0)
#define GET_BONE_MATRIX(a, b, w) mat2x4(TEX(a), TEX(b)) * w

	uvec4 bones = in_bone_attrib * uvec4(2u);
	uvec4 bones_a = bones + uvec4(1u);

	highp mat2x4 m = GET_BONE_MATRIX(bones.x, bones_a.x, in_weight_attrib.x);
	m += GET_BONE_MATRIX(bones.y, bones_a.y, in_weight_attrib.y);
	m += GET_BONE_MATRIX(bones.z, bones_a.z, in_weight_attrib.z);
	m += GET_BONE_MATRIX(bones.w, bones_a.w, in_weight_attrib.w);

	mat4 skeleton_matrix = mat4(vec4(skeleton_transform_x, 0.0, 0.0), vec4(skeleton_transform_y, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(skeleton_transform_offset, 0.0, 1.0));
	mat4 inverse_matrix = mat4(vec4(inverse_transform_x, 0.0, 0.0), vec4(inverse_transform_y, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(inverse_transform_offset, 0.0, 1.0));
	mat4 bone_matrix = mat4(m[0], m[1], vec4(0.0, 0.0, 1.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0));

	bone_matrix = skeleton_matrix * transpose(bone_matrix) * inverse_matrix;

	out_vertex = (bone_matrix * vec4(out_vertex, 0.0, 1.0)).xy;
#endif // USE_SKELETON

#else // MODE_2D

#ifdef USE_BLEND_SHAPES
#ifdef MODE_BLEND_PASS
	out_vertex = in_vertex + blend_vertex * blend_weight;

#ifdef USE_NORMAL
	vec3 normal = vec2_to_vec4(in_normal).xyz * blend_shape_count;
	vec3 normal_blend = oct_to_vec3(blend_normal) * blend_weight;
#ifdef FINAL_PASS
	out_normal = vec3_to_oct(normalize(normal + normal_blend));
#else
	out_normal = vec4_to_vec2(vec4(normal + normal_blend, 0.0) / blend_shape_count);
#endif
#endif // USE_NORMAL

#ifdef USE_TANGENT
	vec4 tangent = vec2_to_vec4(in_tangent) * blend_shape_count;
	vec4 tangent_blend = oct_to_tang(blend_tangent) * blend_weight;
#ifdef FINAL_PASS
	out_tangent = tang_to_oct(vec4(normalize(tangent.xyz + tangent_blend.xyz), tangent.w));
#else
	out_tangent = vec4_to_vec2(vec4((tangent.xyz + tangent_blend.xyz) / blend_shape_count, tangent.w));
#endif
#endif // USE_TANGENT

#else // MODE_BLEND_PASS
	out_vertex = in_vertex * blend_weight;

#ifdef USE_NORMAL
	vec3 normal = oct_to_vec3(in_normal);
	out_normal = vec4_to_vec2(vec4(normal * blend_weight / blend_shape_count, 0.0));
#endif
#ifdef USE_TANGENT
	vec4 tangent = oct_to_tang(in_tangent);
	out_tangent = vec4_to_vec2(vec4(tangent.rgb * blend_weight / blend_shape_count, tangent.w));
#endif
#endif // MODE_BLEND_PASS
#else // USE_BLEND_SHAPES

	// Make attributes available to the skeleton shader if not written by blend shapes.
	out_vertex = in_vertex;
#ifdef USE_NORMAL
	out_normal = in_normal;
#endif
#ifdef USE_TANGENT
	out_tangent = in_tangent;
#endif
#endif // USE_BLEND_SHAPES

#ifdef USE_SKELETON

#define TEX(m) texelFetch(skeleton_texture, ivec2(m % 256u, m / 256u), 0)
#define GET_BONE_MATRIX(a, b, c, w) mat4(TEX(a), TEX(b), TEX(c), vec4(0.0, 0.0, 0.0, 1.0)) * w

	uvec4 bones = in_bone_attrib * uvec4(3);
	uvec4 bones_a = bones + uvec4(1);
	uvec4 bones_b = bones + uvec4(2);

	highp mat4 m;
	m = GET_BONE_MATRIX(bones.x, bones_a.x, bones_b.x, in_weight_attrib.x);
	m += GET_BONE_MATRIX(bones.y, bones_a.y, bones_b.y, in_weight_attrib.y);
	m += GET_BONE_MATRIX(bones.z, bones_a.z, bones_b.z, in_weight_attrib.z);
	m += GET_BONE_MATRIX(bones.w, bones_a.w, bones_b.w, in_weight_attrib.w);

#ifdef USE_EIGHT_WEIGHTS
	bones = in_bone_attrib2 * uvec4(3);
	bones_a = bones + uvec4(1);
	bones_b = bones + uvec4(2);

	m += GET_BONE_MATRIX(bones.x, bones_a.x, bones_b.x, in_weight_attrib2.x);
	m += GET_BONE_MATRIX(bones.y, bones_a.y, bones_b.y, in_weight_attrib2.y);
	m += GET_BONE_MATRIX(bones.z, bones_a.z, bones_b.z, in_weight_attrib2.z);
	m += GET_BONE_MATRIX(bones.w, bones_a.w, bones_b.w, in_weight_attrib2.w);
#endif

	// Reverse order because its transposed.
	out_vertex = (vec4(out_vertex, 1.0) * m).xyz;
#ifdef USE_NORMAL
	vec3 vertex_normal = oct_to_vec3(out_normal);
	out_normal = vec3_to_oct(normalize((vec4(vertex_normal, 0.0) * m).xyz));
#endif // USE_NORMAL
#ifdef USE_TANGENT
	vec4 vertex_tangent = oct_to_tang(out_tangent);
	out_tangent = tang_to_oct(vec4(normalize((vec4(vertex_tangent.xyz, 0.0) * m).xyz), vertex_tangent.w));
#endif // USE_TANGENT
#endif // USE_SKELETON
#endif // MODE_2D
}

/* clang-format off */
)<!>"
		};

		static const char _fragment_code[] = {
R"<!>(
void main() {

}
/* clang-format on */
)<!>"
		};

		_setup(_vertex_code, _fragment_code, "SkeletonShaderGLES3",
				8, _uniform_strings, 0, _ubo_pairs,
				3, _feedbacks, 1, _texunit_pairs,
				7, _spec_pairs, 2, _variant_defines);
	}
};
