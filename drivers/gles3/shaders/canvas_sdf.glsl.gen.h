/**************************************************************************/
/*  canvas_sdf.glsl.gen.h                                                 */
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

class CanvasSdfShaderGLES3 : public ShaderGLES3 {
public:
	enum Uniforms {
		SIZE,
		STRIDE,
		SHIFT,
		BASE_SIZE,
	};

	enum ShaderVariant {
		MODE_LOAD,
		MODE_LOAD_SHRINK,
		MODE_PROCESS,
		MODE_STORE,
		MODE_STORE_SHRINK,
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
			"size",
			"stride",
			"shift",
			"base_size"
		};
		static const char *_variant_defines[] = {
			"#define MODE_LOAD",
			"#define MODE_LOAD_SHRINK",
			"#define MODE_PROCESS",
			"#define MODE_STORE",
			"#define MODE_STORE_SHRINK",
		};
		static TexUnitPair _texunit_pairs[] = {
			{ "src_pixels", 0 },
			{ "src_process", 0 },
		};
		static UBOPair *_ubo_pairs = nullptr;
		static Specialization *_spec_pairs = nullptr;
		static const Feedback *_feedbacks = nullptr;
		static const char _vertex_code[] = {
R"<!>(
layout(location = 0) in vec2 vertex_attrib;

/* clang-format on */

uniform ivec2 size;
uniform int stride;
uniform int shift;
uniform ivec2 base_size;

void main() {
	gl_Position = vec4(vertex_attrib, 1.0, 1.0);
}

/* clang-format off */
)<!>"
		};

		static const char _fragment_code[] = {
R"<!>(
#define SDF_MAX_LENGTH 16384.0

#if defined(MODE_LOAD) || defined(MODE_LOAD_SHRINK)
uniform lowp sampler2D src_pixels;//texunit:0
#else
uniform highp isampler2D src_process;//texunit:0
#endif

uniform	ivec2 size;
uniform	int stride;
uniform	int shift;
uniform	ivec2 base_size;

#if defined(MODE_LOAD) || defined(MODE_LOAD_SHRINK) || defined(MODE_PROCESS)
layout(location = 0) out ivec4 distance_field;
#else
layout(location = 0) out vec4 distance_field;
#endif

vec4 float_to_vec4(float p_float) {
    highp vec4 comp = fract(p_float * vec4(255.0 * 255.0 * 255.0, 255.0 * 255.0, 255.0, 1.0));
	comp -= comp.xxyz * vec4(0.0, 1.0 / 255.0, 1.0 / 255.0, 1.0 / 255.0);
	return comp;
}

void main() {
	ivec2 pos = ivec2(gl_FragCoord.xy);

#ifdef MODE_LOAD

	bool solid = texelFetch(src_pixels, pos, 0).r > 0.5;
	distance_field = solid ? ivec4(ivec2(-32767), 0, 0) : ivec4(ivec2(32767), 0, 0);
#endif

#ifdef MODE_LOAD_SHRINK

	int s = 1 << shift;
	ivec2 base = pos << shift;
	ivec2 center = base + ivec2(shift);

	ivec2 rel = ivec2(32767);
	float d = 1e20;
	int found = 0;
	int solid_found = 0;
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			ivec2 src_pos = base + ivec2(i, j);
			if (any(greaterThanEqual(src_pos, base_size))) {
				continue;
			}
			bool solid = texelFetch(src_pixels, src_pos, 0).r > 0.5;
			if (solid) {
				float dist = length(vec2(src_pos - center));
				if (dist < d) {
					d = dist;
					rel = src_pos;
				}
				solid_found++;
			}
			found++;
		}
	}

	if (solid_found == found) {
		//mark solid only if all are solid
		rel = ivec2(-32767);
	}

	distance_field = ivec4(rel, 0, 0);
#endif

#ifdef MODE_PROCESS

	ivec2 base = pos << shift;
	ivec2 center = base + ivec2(shift);

	ivec2 rel = texelFetch(src_process, pos, 0).xy;

	bool solid = rel.x < 0;

	if (solid) {
		rel = -rel - ivec2(1);
	}

	if (center != rel) {
		//only process if it does not point to itself
		const int ofs_table_size = 8;
		const ivec2 ofs_table[ofs_table_size] = ivec2[](
				ivec2(-1, -1),
				ivec2(0, -1),
				ivec2(+1, -1),

				ivec2(-1, 0),
				ivec2(+1, 0),

				ivec2(-1, +1),
				ivec2(0, +1),
				ivec2(+1, +1));

		float dist = length(vec2(rel - center));
		for (int i = 0; i < ofs_table_size; i++) {
			ivec2 src_pos = pos + ofs_table[i] * stride;
			if (any(lessThan(src_pos, ivec2(0))) || any(greaterThanEqual(src_pos, size))) {
				continue;
			}
			ivec2 src_rel = texelFetch(src_process, src_pos, 0).xy;
			bool src_solid = src_rel.x < 0;
			if (src_solid) {
				src_rel = -src_rel - ivec2(1);
			}

			if (src_solid != solid) {
				src_rel = ivec2(src_pos << shift); //point to itself if of different type
			}

			float src_dist = length(vec2(src_rel - center));
			if (src_dist < dist) {
				dist = src_dist;
				rel = src_rel;
			}
		}
	}

	if (solid) {
		rel = -rel - ivec2(1);
	}

	distance_field = ivec4(rel, 0, 0);
#endif

#ifdef MODE_STORE

	ivec2 rel = texelFetch(src_process, pos, 0).xy;

	bool solid = rel.x < 0;

	if (solid) {
		rel = -rel - ivec2(1);
	}

	float d = length(vec2(rel - pos));

	if (solid) {
		d = -d;
	}

	d /= SDF_MAX_LENGTH;
	d = clamp(d, -1.0, 1.0);
	distance_field = float_to_vec4(d*0.5+0.5);

#endif

#ifdef MODE_STORE_SHRINK

	ivec2 base = pos << shift;
	ivec2 center = base + ivec2(shift);

	ivec2 rel = texelFetch(src_process, pos, 0).xy;

	bool solid = rel.x < 0;

	if (solid) {
		rel = -rel - ivec2(1);
	}

	float d = length(vec2(rel - center));

	if (solid) {
		d = -d;
	}
	d /= SDF_MAX_LENGTH;
	d = clamp(d, -1.0, 1.0);
	distance_field = float_to_vec4(d*0.5+0.5);

#endif
}
)<!>"
		};

		_setup(_vertex_code, _fragment_code, "CanvasSdfShaderGLES3",
				4, _uniform_strings, 0, _ubo_pairs,
				0, _feedbacks, 2, _texunit_pairs,
				0, _spec_pairs, 5, _variant_defines);
	}
};
