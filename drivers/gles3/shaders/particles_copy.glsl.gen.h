/**************************************************************************/
/*  particles_copy.glsl.gen.h                                             */
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

class ParticlesCopyShaderGLES3 : public ShaderGLES3 {
public:
	enum Uniforms {
		SORT_DIRECTION,
		FRAME_REMAINDER,
		ALIGN_UP,
		ALIGN_MODE,
		INV_EMISSION_TRANSFORM,
		ALIGN_CHANNEL_FILTER,
		ALIGN_AXIS,
	};

	enum ShaderVariant {
		MODE_DEFAULT,
	};

	enum Specializations {
		MODE_3D = 1,
	};

	_FORCE_INLINE_ bool version_bind_shader(RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		return _version_bind_shader(p_version, p_variant, p_specialization);
	}

	_FORCE_INLINE_ int version_get_uniform(Uniforms p_uniform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		return _version_get_uniform(p_uniform, p_version, p_variant, p_specialization);
	}

	/* clang-format off */
#define TRY_GET_UNIFORM(var_name) int var_name = version_get_uniform(p_uniform, p_version, p_variant, p_specialization); if (var_name < 0) return
	/* clang-format on */

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1f(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, double p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1f(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint8_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int8_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint16_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int16_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint32_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int32_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Color &p_color, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat col[4] = { p_color.r, p_color.g, p_color.b, p_color.a };
		glUniform4fv(uniform_location, 1, col);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector2 &p_vec2, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec2[2] = { float(p_vec2.x), float(p_vec2.y) };
		glUniform2fv(uniform_location, 1, vec2);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Size2i &p_vec2, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		GLint vec2[2] = { GLint(p_vec2.x), GLint(p_vec2.y) };
		glUniform2iv(uniform_location, 1, vec2);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector3 &p_vec3, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec3[3] = { float(p_vec3.x), float(p_vec3.y), float(p_vec3.z) };
		glUniform3fv(uniform_location, 1, vec3);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector4 &p_vec4, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec4[4] = { float(p_vec4.x), float(p_vec4.y), float(p_vec4.z), float(p_vec4.w) };
		glUniform4fv(uniform_location, 1, vec4);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform2f(uniform_location, p_a, p_b);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, float p_c, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform3f(uniform_location, p_a, p_b, p_c);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, float p_c, float p_d, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform4f(uniform_location, p_a, p_b, p_c, p_d);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Transform3D &p_transform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
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

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Transform2D &p_transform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
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

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Projection &p_matrix, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
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
			"sort_direction",
			"frame_remainder",
			"align_up",
			"align_mode",
			"inv_emission_transform",
			"align_channel_filter",
			"align_axis"
		};
		static const char *_variant_defines[] = {
			"",
		};
		static TexUnitPair *_texunit_pairs = nullptr;
		static UBOPair *_ubo_pairs = nullptr;
		static Specialization _spec_pairs[] = {
			{ "MODE_3D", false },
		};
		static const Feedback _feedbacks[] = {
			{ "out_xform_1", 0 },
			{ "out_xform_2", 0 },
			{ "out_xform_3", 1 },
			{ "instance_color_custom_data", 0 },
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

// ParticleData
layout(location = 0) in highp vec4 color;
layout(location = 1) in highp vec4 velocity_flags;
layout(location = 2) in highp vec4 custom;
layout(location = 3) in highp vec4 xform_1;
layout(location = 4) in highp vec4 xform_2;
#ifdef MODE_3D
layout(location = 5) in highp vec4 xform_3;
#endif

/* clang-format on */
out highp vec4 out_xform_1; //tfb:
out highp vec4 out_xform_2; //tfb:
#ifdef MODE_3D
out highp vec4 out_xform_3; //tfb:MODE_3D
#endif
flat out highp uvec4 instance_color_custom_data; //tfb:

uniform lowp vec3 sort_direction;
uniform highp float frame_remainder;

uniform highp vec3 align_up;
uniform highp uint align_mode;

uniform highp mat4 inv_emission_transform;

uniform uint align_channel_filter;
uniform uint align_axis;

#define ALIGN_DISABLED uint(0)
#define ALIGN_BILLBOARD uint(1)
#define ALIGN_Y_TO_VELOCITY uint(2)
#define ALIGN_Z_BILLBOARD_Y_TO_VELOCITY uint(3)
#define ALIGN_LOCAL_BILLBOARD uint(4)

#define CHANNEL_FILTER_NONE uint(0)
#define CHANNEL_FILTER_X uint(1)
#define CHANNEL_FILTER_Y uint(2)
#define CHANNEL_FILTER_Z uint(3)
#define CHANNEL_FILTER_W uint(4)

#define ALIGN_AXIS_X uint(0)
#define ALIGN_AXIS_Y uint(1)
#define ALIGN_AXIS_Z uint(2)

#define PARTICLE_FLAG_ACTIVE uint(1)

#define FLT_MAX float(3.402823466e+38)

void main() {
	// Set scale to zero and translate to -INF so particle will be invisible
	// even for materials that ignore rotation/scale (i.e. billboards).
	mat4 txform = mat4(vec4(0.0), vec4(0.0), vec4(0.0), vec4(-FLT_MAX, -FLT_MAX, -FLT_MAX, 0.0));
	if (bool(floatBitsToUint(velocity_flags.w) & PARTICLE_FLAG_ACTIVE)) {
#ifdef MODE_3D
		txform = transpose(mat4(xform_1, xform_2, xform_3, vec4(0.0, 0.0, 0.0, 1.0)));
#else
		txform = transpose(mat4(xform_1, xform_2, vec4(0.0, 0.0, 1.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0)));
#endif

		if (align_mode == ALIGN_DISABLED) {
			// nothing
		} else if (align_mode == ALIGN_BILLBOARD) {
			float angle = 0.;
			if (align_channel_filter == CHANNEL_FILTER_NONE) {
				mat3 local = mat3(normalize(cross(align_up, sort_direction)), align_up, sort_direction);
				local = local * mat3(txform);
				txform[0].xyz = local[0];
				txform[1].xyz = local[1];
				txform[2].xyz = local[2];
			} else {
				if (align_channel_filter == CHANNEL_FILTER_X) {
					angle = custom.x;

				} else if (align_channel_filter == CHANNEL_FILTER_Y) {
					angle = custom.y;

				} else if (align_channel_filter == CHANNEL_FILTER_Z) {
					angle = custom.z;

				} else if (align_channel_filter == CHANNEL_FILTER_W) {
					angle = custom.w;
				}

				vec3 axis = normalize(sort_direction);
				float s = sin(angle);
				float c = cos(angle);
				float oc = 1.0 - c;
				mat3 rotated = mat3(
						oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s,
						oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s,
						oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c);
				vec3 new_up = rotated * align_up;
				mat3 local = mat3(normalize(cross(new_up, sort_direction)), new_up, sort_direction);
				local = local * mat3(txform);
				txform[0].xyz = local[0];
				txform[1].xyz = local[1];
				txform[2].xyz = local[2];
			}
		} else if (align_mode == ALIGN_Y_TO_VELOCITY) {
			vec3 v = velocity_flags.xyz;
			float s = (length(txform[0]) + length(txform[1]) + length(txform[2])) / 3.0;
			if (length(v) > 0.0) {
				txform[1].xyz = normalize(v);
			} else {
				txform[1].xyz = normalize(txform[1].xyz);
			}

			txform[0].xyz = normalize(cross(txform[1].xyz, txform[2].xyz));
			txform[2].xyz = vec3(0.0, 0.0, 1.0) * s;
			txform[0].xyz *= s;
			txform[1].xyz *= s;
		} else if (align_mode == ALIGN_Z_BILLBOARD_Y_TO_VELOCITY) {
			vec3 sv = velocity_flags.xyz - sort_direction * dot(sort_direction, velocity_flags.xyz); //screen velocity

			if (length(sv) == 0.0) {
				sv = align_up;
			}

			sv = normalize(sv);

			txform[0].xyz = normalize(cross(sv, sort_direction)) * length(txform[0]);
			txform[1].xyz = sv * length(txform[1]);
			txform[2].xyz = sort_direction * length(txform[2]);
		} else if (align_mode == ALIGN_LOCAL_BILLBOARD) {
			if (align_axis == ALIGN_AXIS_X) {
				vec3 len = vec3(
						length(txform[0].xyz),
						length(txform[1].xyz),
						length(txform[2].xyz));
				txform[0].xyz = normalize(txform[0].xyz);
				txform[1].xyz = normalize(cross(sort_direction, txform[0].xyz));
				txform[2].xyz = cross(txform[0].xyz, txform[1].xyz);

				txform[0].xyz *= len.x;
				txform[1].xyz *= len.y;
				txform[2].xyz *= len.z;
			} else if (align_axis == ALIGN_AXIS_Y) {
				vec3 len = vec3(
						length(txform[0].xyz),
						length(txform[1].xyz),
						length(txform[2].xyz));
				txform[1].xyz = normalize(txform[1].xyz);
				txform[0].xyz = normalize(cross(txform[1].xyz, sort_direction));
				txform[2].xyz = cross(txform[0].xyz, txform[1].xyz);

				txform[0].xyz *= len.x;
				txform[1].xyz *= len.y;
				txform[2].xyz *= len.z;
			}
		}

		txform[3].xyz += velocity_flags.xyz * frame_remainder;

#ifndef MODE_3D
		// In global mode, bring 2D particles to local coordinates
		// as they will be drawn with the node position as origin.
		txform = inv_emission_transform * txform;
#endif
	}
	txform = transpose(txform);

	instance_color_custom_data.x = packHalf2x16(color.xy);
	instance_color_custom_data.y = packHalf2x16(color.zw);
	instance_color_custom_data.z = packHalf2x16(custom.xy);
	instance_color_custom_data.w = packHalf2x16(custom.zw);
	out_xform_1 = txform[0];
	out_xform_2 = txform[1];
#ifdef MODE_3D
	out_xform_3 = txform[2];
#endif
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

		_setup(_vertex_code, _fragment_code, "ParticlesCopyShaderGLES3",
				7, _uniform_strings, 0, _ubo_pairs,
				4, _feedbacks, 0, _texunit_pairs,
				1, _spec_pairs, 1, _variant_defines);
	}
};
