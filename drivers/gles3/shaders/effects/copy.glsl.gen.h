/**************************************************************************/
/*  copy.glsl.gen.h                                                       */
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

class CopyShaderGLES3 : public ShaderGLES3 {
public:
	enum Uniforms {
		COPY_SECTION,
		SOURCE_SECTION,
		LAYER,
		LOD,
		COLOR_IN,
		MULTIPLY,
		PIXEL_SIZE,
		MIP_LEVEL,
		EYE_CENTER,
		K1,
		K2,
		UPSCALE,
		ASPECT_RATIO,
		EXPOSURE,
	};

	enum ShaderVariant {
		MODE_DEFAULT,
		MODE_COPY_SECTION,
		MODE_COPY_SECTION_SOURCE,
		MODE_COPY_SECTION_3D,
		MODE_COPY_SECTION_2D_ARRAY,
		MODE_LENS_DISTORTION,
		MODE_SCREEN,
		MODE_GAUSSIAN_BLUR,
		MODE_MIPMAP,
		MODE_SIMPLE_COLOR,
		MODE_CUBE_TO_OCTAHEDRAL,
		MODE_CUBE_TO_PANORAMA,
		MODE_APPLY_LINEAR_EXPOSURE_TO_SRGB,
	};

	enum Specializations {
		CONVERT_LINEAR_TO_SRGB = 1,
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
			"copy_section",
			"source_section",
			"layer",
			"lod",
			"color_in",
			"multiply",
			"pixel_size",
			"mip_level",
			"eye_center",
			"k1",
			"k2",
			"upscale",
			"aspect_ratio",
			"exposure"
		};
		static const char *_variant_defines[] = {
			"#define MODE_SIMPLE_COPY",
			"#define USE_COPY_SECTION \n#define MODE_SIMPLE_COPY",
			"#define USE_COPY_SECTION \n#define MODE_SIMPLE_COPY \n#define MODE_COPY_FROM",
			"#define USE_COPY_SECTION \n#define MODE_SIMPLE_COPY \n#define USE_TEXTURE_3D",
			"#define USE_COPY_SECTION \n#define MODE_SIMPLE_COPY \n#define USE_TEXTURE_2D_ARRAY",
			"#define USE_COPY_SECTION \n#define MODE_SIMPLE_COPY \n#define USE_TEXTURE_2D_ARRAY \n#define APPLY_LENS_DISTORTION",
			"#define MODE_SIMPLE_COPY \n#define MODE_MULTIPLY",
			"#define MODE_GAUSSIAN_BLUR",
			"#define MODE_MIPMAP",
			"#define MODE_SIMPLE_COLOR \n#define USE_COPY_SECTION",
			"#define CUBE_TO_OCTAHEDRAL \n#define USE_COPY_SECTION",
			"#define CUBE_TO_PANORAMA",
			"#define MODE_SIMPLE_COPY \n#define MODE_MULTIPLY \n#define APPLY_LINEAR_EXPOSURE_TO_SRGB",
		};
		static TexUnitPair _texunit_pairs[] = {
			{ "source_cube", 0 },
			{ "source_3d", 0 },
			{ "source_2d_array", 0 },
			{ "source", 0 },
		};
		static UBOPair *_ubo_pairs = nullptr;
		static Specialization _spec_pairs[] = {
			{ "CONVERT_LINEAR_TO_SRGB", false },
		};
		static const Feedback *_feedbacks = nullptr;
		static const char _vertex_code[] = {
R"<!>(
layout(location = 0) in vec2 vertex_attrib;

out vec2 uv_interp;
/* clang-format on */

#if defined(USE_COPY_SECTION) || defined(MODE_GAUSSIAN_BLUR)
// Defined in 0-1 coords.
uniform highp vec4 copy_section;
#endif
#if defined(MODE_GAUSSIAN_BLUR) || defined(MODE_COPY_FROM)
uniform highp vec4 source_section;
#endif

void main() {
	uv_interp = vertex_attrib * 0.5 + 0.5;
	gl_Position = vec4(vertex_attrib, 1.0, 1.0);

#if defined(USE_COPY_SECTION) || defined(MODE_GAUSSIAN_BLUR)
	gl_Position.xy = (copy_section.xy + uv_interp.xy * copy_section.zw) * 2.0 - 1.0;
#endif
#if defined(MODE_GAUSSIAN_BLUR) || defined(MODE_COPY_FROM)
	uv_interp = source_section.xy + uv_interp * source_section.zw;
#endif
}

/* clang-format off */
)<!>"
		};

		static const char _fragment_code[] = {
R"<!>(
in vec2 uv_interp;
/* clang-format on */
#if defined(USE_TEXTURE_3D) || defined(USE_TEXTURE_2D_ARRAY)
uniform float layer;
uniform float lod;
#endif

#ifdef MODE_SIMPLE_COLOR
uniform vec4 color_in;
#endif

#ifdef MODE_MULTIPLY
uniform float multiply;
#endif

#ifdef MODE_GAUSSIAN_BLUR
// Defined in 0-1 coords.
uniform highp vec2 pixel_size;
#endif

#ifdef CUBE_TO_OCTAHEDRAL
vec3 oct_to_vec3(vec2 e) {
	vec3 v = vec3(e.xy, 1.0 - abs(e.x) - abs(e.y));
	float t = max(-v.z, 0.0);
	v.xy += t * -sign(v.xy);
	return normalize(v);
}
#endif

#ifdef CUBE_TO_PANORAMA
uniform lowp float mip_level;
#endif

#if defined(CUBE_TO_OCTAHEDRAL) || defined(CUBE_TO_PANORAMA)
uniform samplerCube source_cube; // texunit:0

#else // ~(defined(CUBE_TO_OCTAHEDRAL) || defined(CUBE_TO_PANORAMA))

#if defined(USE_TEXTURE_3D)
uniform sampler3D source_3d; // texunit:0
#elif defined(USE_TEXTURE_2D_ARRAY)
uniform sampler2DArray source_2d_array; // texunit:0
#else
uniform sampler2D source; // texunit:0
#endif

#endif // !(defined(CUBE_TO_OCTAHEDRAL) || defined(CUBE_TO_PANORAMA))

#ifdef APPLY_LENS_DISTORTION
uniform vec2 eye_center;
uniform float k1;
uniform float k2;
uniform float upscale;
uniform float aspect_ratio;
#endif // APPLY_LENS_DISTORTION

#ifdef APPLY_LINEAR_EXPOSURE_TO_SRGB
uniform float exposure;
#endif

layout(location = 0) out vec4 frag_color;

// This approximation expects non-negative input; negative input behaves poorly.
vec3 srgb_to_linear(vec3 color) {
	// Approximation from http://chilliant.blogspot.com/2012/08/srgb-approximations-for-hlsl.html
	return color * (color * (color * 0.305306011 + 0.682171111) + 0.012522878);
}

// This approximation expects non-negative input; negative input is undefined behavior.
vec3 linear_to_srgb(vec3 color) {
	// Approximation from http://chilliant.blogspot.com/2012/08/srgb-approximations-for-hlsl.html
	return max(vec3(1.055) * pow(color, vec3(0.416666667)) - vec3(0.055), vec3(0.0));
}

void main() {
#ifdef MODE_SIMPLE_COPY

	vec2 uv = uv_interp;

#ifdef APPLY_LENS_DISTORTION
	uv = uv * 2.0 - 1.0;
	vec2 offset = uv - eye_center;

	// take aspect ratio into account
	offset.y /= aspect_ratio;

	// distort
	vec2 offset_sq = offset * offset;
	float radius_sq = offset_sq.x + offset_sq.y;
	float radius_s4 = radius_sq * radius_sq;
	float distortion_scale = 1.0 + (k1 * radius_sq) + (k2 * radius_s4);
	offset *= distortion_scale;

	// reapply aspect ratio
	offset.y *= aspect_ratio;

	// add our eye center back in
	uv = offset + eye_center;
	uv /= upscale;

	// and check our color
	if (uv.x < -1.0 || uv.y < -1.0 || uv.x > 1.0 || uv.y > 1.0) {
		frag_color = vec4(0.0, 0.0, 0.0, 1.0);
	} else {
		uv = uv * 0.5 + 0.5;
#endif // APPLY_LENS_DISTORTION

#ifdef USE_TEXTURE_3D
		vec4 color = textureLod(source_3d, vec3(uv, layer), lod);
#elif defined(USE_TEXTURE_2D_ARRAY)
	vec4 color = textureLod(source_2d_array, vec3(uv, layer), lod);
#else
	vec4 color = texture(source, uv);
#endif // USE_TEXTURE_3D

#ifdef CONVERT_LINEAR_TO_SRGB
		// Reading from a *_SRGB texture source will have converted data to linear,
		// but we should output in sRGB!
		color.rgb = linear_to_srgb(color.rgb);
#endif

#ifdef APPLY_LINEAR_EXPOSURE_TO_SRGB
		color.rgb = srgb_to_linear(color.rgb);
		color.rgb *= exposure;
		color.rgb = linear_to_srgb(color.rgb);
#endif

#ifdef MODE_MULTIPLY
		color *= multiply;
#endif // MODE_MULTIPLY

		frag_color = color;

#ifdef APPLY_LENS_DISTORTION
	}
#endif // APPLY_LENS_DISTORTION

#endif // MODE_SIMPLE_COPY

#ifdef MODE_SIMPLE_COLOR
	frag_color = color_in;
#endif

// Efficient box filter from Jimenez: http://www.iryoku.com/next-generation-post-processing-in-call-of-duty-advanced-warfare
// Approximates a Gaussian in a single pass.
#ifdef MODE_GAUSSIAN_BLUR
	vec4 A = textureLod(source, uv_interp + pixel_size * vec2(-1.0, -1.0), 0.0);
	vec4 B = textureLod(source, uv_interp + pixel_size * vec2(0.0, -1.0), 0.0);
	vec4 C = textureLod(source, uv_interp + pixel_size * vec2(1.0, -1.0), 0.0);
	vec4 D = textureLod(source, uv_interp + pixel_size * vec2(-0.5, -0.5), 0.0);
	vec4 E = textureLod(source, uv_interp + pixel_size * vec2(0.5, -0.5), 0.0);
	vec4 F = textureLod(source, uv_interp + pixel_size * vec2(-1.0, 0.0), 0.0);
	vec4 G = textureLod(source, uv_interp, 0.0);
	vec4 H = textureLod(source, uv_interp + pixel_size * vec2(1.0, 0.0), 0.0);
	vec4 I = textureLod(source, uv_interp + pixel_size * vec2(-0.5, 0.5), 0.0);
	vec4 J = textureLod(source, uv_interp + pixel_size * vec2(0.5, 0.5), 0.0);
	vec4 K = textureLod(source, uv_interp + pixel_size * vec2(-1.0, 1.0), 0.0);
	vec4 L = textureLod(source, uv_interp + pixel_size * vec2(0.0, 1.0), 0.0);
	vec4 M = textureLod(source, uv_interp + pixel_size * vec2(1.0, 1.0), 0.0);

	float weight = 0.5 / 4.0;
	float lesser_weight = 0.125 / 4.0;

	frag_color = (D + E + I + J) * weight;
	frag_color += (A + B + G + F) * lesser_weight;
	frag_color += (B + C + H + G) * lesser_weight;
	frag_color += (F + G + L + K) * lesser_weight;
	frag_color += (G + H + M + L) * lesser_weight;
#endif

#ifdef CUBE_TO_OCTAHEDRAL
	// Treat the UV coordinates as 0-1 encoded octahedral coordinates.
	vec3 dir = oct_to_vec3(uv_interp * 2.0 - 1.0);
	frag_color = texture(source_cube, dir);

#endif

#ifdef CUBE_TO_PANORAMA

	const float PI = 3.14159265359;

	float phi = uv_interp.x * 2.0 * PI;
	float theta = uv_interp.y * PI;

	vec3 normal;
	normal.x = sin(phi) * sin(theta) * -1.0;
	normal.y = cos(theta);
	normal.z = cos(phi) * sin(theta) * -1.0;

	vec3 color = srgb_to_linear(textureLod(source_cube, normal, mip_level).rgb);
	frag_color = vec4(color, 1.0);

#endif
}
)<!>"
		};

		_setup(_vertex_code, _fragment_code, "CopyShaderGLES3",
				14, _uniform_strings, 0, _ubo_pairs,
				0, _feedbacks, 4, _texunit_pairs,
				1, _spec_pairs, 13, _variant_defines);
	}
};
