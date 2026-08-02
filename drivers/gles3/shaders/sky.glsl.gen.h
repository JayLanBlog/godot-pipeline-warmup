/**************************************************************************/
/*  sky.glsl.gen.h                                                        */
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

class SkyShaderGLES3 : public ShaderGLES3 {
public:
	enum Uniforms {
		GLOBAL_SHADER_S,
		ORIENTATION,
		PROJECTION,
		POSITION,
		TIME,
		SKY_ENERGY_MULTIPLIER,
		LUMINANCE_MULTIPLIER,
		FOG_AERIAL_PERSPECTIVE,
		FOG_LIGHT_COLOR,
		FOG_SUN_SCATTER,
		FOG_ENABLED,
		FOG_DENSITY,
		FOG_SKY_AFFECT,
		DIRECTIONAL_LIGHT_COUNT,
	};

	enum ShaderVariant {
		MODE_BACKGROUND,
		MODE_CUBEMAP,
	};

	enum Specializations {
		USE_MULTIVIEW = 1,
		USE_INVERTED_Y = 2,
		APPLY_TONEMAPPING = 4,
		USE_QUARTER_RES_PASS = 8,
		USE_HALF_RES_PASS = 16,
	};

	_FORCE_INLINE_ bool version_bind_shader(RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		return _version_bind_shader(p_version, p_variant, p_specialization);
	}

	_FORCE_INLINE_ int version_get_uniform(Uniforms p_uniform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		return _version_get_uniform(p_uniform, p_version, p_variant, p_specialization);
	}

	/* clang-format off */
#define TRY_GET_UNIFORM(var_name) int var_name = version_get_uniform(p_uniform, p_version, p_variant, p_specialization); if (var_name < 0) return
	/* clang-format on */

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1f(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, double p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1f(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint8_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int8_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint16_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int16_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, uint32_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1ui(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, int32_t p_value, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform1i(uniform_location, p_value);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Color &p_color, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat col[4] = { p_color.r, p_color.g, p_color.b, p_color.a };
		glUniform4fv(uniform_location, 1, col);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector2 &p_vec2, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec2[2] = { float(p_vec2.x), float(p_vec2.y) };
		glUniform2fv(uniform_location, 1, vec2);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Size2i &p_vec2, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		GLint vec2[2] = { GLint(p_vec2.x), GLint(p_vec2.y) };
		glUniform2iv(uniform_location, 1, vec2);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector3 &p_vec3, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec3[3] = { float(p_vec3.x), float(p_vec3.y), float(p_vec3.z) };
		glUniform3fv(uniform_location, 1, vec3);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Vector4 &p_vec4, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		GLfloat vec4[4] = { float(p_vec4.x), float(p_vec4.y), float(p_vec4.z), float(p_vec4.w) };
		glUniform4fv(uniform_location, 1, vec4);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform2f(uniform_location, p_a, p_b);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, float p_c, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform3f(uniform_location, p_a, p_b, p_c);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, float p_a, float p_b, float p_c, float p_d, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
		TRY_GET_UNIFORM(uniform_location);
		glUniform4f(uniform_location, p_a, p_b, p_c, p_d);
	}

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Transform3D &p_transform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
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

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Transform2D &p_transform, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
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

	_FORCE_INLINE_ void version_set_uniform(Uniforms p_uniform, const Projection &p_matrix, RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 6) {
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
			"global_shader_s",
			"orientation",
			"projection",
			"position",
			"time",
			"sky_energy_multiplier",
			"luminance_multiplier",
			"fog_aerial_perspective",
			"fog_light_color",
			"fog_sun_scatter",
			"fog_enabled",
			"fog_density",
			"fog_sky_affect",
			"directional_light_count"
		};
		static const char *_variant_defines[] = {
			"",
			"#define USE_CUBEMAP_PASS",
		};
		static TexUnitPair _texunit_pairs[] = {
			{ "radiance", -2 },
			{ "half_res", -2 },
			{ "quarter_res", -3 },
		};
		static UBOPair _ubo_pairs[] = {
			{ "TonemapData", 0 },
			{ "GlobalShaderUniformData", 1 },
			{ "DirectionalLights", 4 },
			{ "MaterialUniforms", 3 },
			{ "MultiviewData", 12 },
		};
		static Specialization _spec_pairs[] = {
			{ "USE_MULTIVIEW", false },
			{ "USE_INVERTED_Y", true },
			{ "APPLY_TONEMAPPING", true },
			{ "USE_QUARTER_RES_PASS", false },
			{ "USE_HALF_RES_PASS", false },
		};
		static const Feedback *_feedbacks = nullptr;
		static const char _vertex_code[] = {
R"<!>(
layout(location = 0) in vec2 vertex_attrib;

out vec2 uv_interp;
/* clang-format on */

void main() {
#ifdef USE_INVERTED_Y
	uv_interp = vertex_attrib;
#else
	// We're doing clockwise culling so flip the order
	uv_interp = vec2(vertex_attrib.x, vertex_attrib.y * -1.0);
#endif
	gl_Position = vec4(uv_interp, -1.0, 1.0);
}

/* clang-format off */
)<!>"
		};

		static const char _fragment_code[] = {
R"<!>(
#define M_PI 3.14159265359

layout(std140) uniform TonemapData { //ubo:0
	float exposure;
	int tonemapper;
	int pad;
	int pad2;
	vec4 tonemapper_params;
	float brightness;
	float contrast;
	float saturation;
	int pad3;
};

// This approximation expects non-negative input; negative input is undefined behavior.
vec3 linear_to_srgb(vec3 color) {
	//const vec3 a = vec3(0.055f);
	//return mix((vec3(1.0f) + a) * pow(color.rgb, vec3(1.0f / 2.4f)) - a, 12.92f * color.rgb, lessThan(color.rgb, vec3(0.0031308f)));
	// Approximation from http://chilliant.blogspot.com/2012/08/srgb-approximations-for-hlsl.html
	return max(vec3(1.055) * pow(color, vec3(0.416666667)) - vec3(0.055), vec3(0.0));
}

// This approximation expects non-negative input; negative input behaves poorly.
vec3 srgb_to_linear(vec3 color) {
	// Approximation from http://chilliant.blogspot.com/2012/08/srgb-approximations-for-hlsl.html
	return color * (color * (color * 0.305306011 + 0.682171111) + 0.012522878);
}

#ifdef APPLY_TONEMAPPING

// Based on Reinhard's extended formula, see equation 4 in https://doi.org/cjbgrt
vec3 tonemap_reinhard(vec3 color) {
	float white_squared = tonemapper_params.x;
	vec3 white_squared_color = white_squared * color;
	// Equivalent to color * (1 + color / white_squared) / (1 + color)
	return (white_squared_color + color * color) / (white_squared_color + white_squared);
}

vec3 tonemap_filmic(vec3 color) {
	// These constants must match the those in the C++ code that calculates the parameters.
	// exposure_bias: Input scale (color *= bias, env->white *= bias) to make the brightness consistent with other tonemappers.
	// Also useful to scale the input to the range that the tonemapper is designed for (some require very high input values).
	// Has no effect on the curve's general shape or visual properties.
	const float exposure_bias = 2.0f;
	const float A = 0.22f * exposure_bias * exposure_bias; // bias baked into constants for performance
	const float B = 0.30f * exposure_bias;
	const float C = 0.10f;
	const float D = 0.20f;
	const float E = 0.01f;
	const float F = 0.30f;

	vec3 color_tonemapped = ((color * (A * color + C * B) + D * E) / (color * (A * color + B) + D * F)) - E / F;

	return color_tonemapped / tonemapper_params.x;
}

// Adapted from https://github.com/TheRealMJP/BakingLab/blob/master/BakingLab/ACES.hlsl
// (MIT License).
vec3 tonemap_aces(vec3 color) {
	// These constants must match the those in the C++ code that calculates the parameters.
	const float exposure_bias = 1.8f;
	const float A = 0.0245786f;
	const float B = 0.000090537f;
	const float C = 0.983729f;
	const float D = 0.432951f;
	const float E = 0.238081f;

	// Exposure bias baked into transform to save shader instructions. Equivalent to `color *= exposure_bias`
	const mat3 rgb_to_rrt = mat3(
			vec3(0.59719f * exposure_bias, 0.35458f * exposure_bias, 0.04823f * exposure_bias),
			vec3(0.07600f * exposure_bias, 0.90834f * exposure_bias, 0.01566f * exposure_bias),
			vec3(0.02840f * exposure_bias, 0.13383f * exposure_bias, 0.83777f * exposure_bias));

	const mat3 odt_to_rgb = mat3(
			vec3(1.60475f, -0.53108f, -0.07367f),
			vec3(-0.10208f, 1.10813f, -0.00605f),
			vec3(-0.00327f, -0.07276f, 1.07602f));

	color *= rgb_to_rrt;
	vec3 color_tonemapped = (color * (color + A) - B) / (color * (C * color + D) + E);
	color_tonemapped *= odt_to_rgb;

	return color_tonemapped / tonemapper_params.x;
}

// allenwp tonemapping curve; developed for use in the Godot game engine.
// Source and details: https://allenwp.com/blog/2025/05/29/allenwp-tonemapping-curve/
// Input must be a non-negative linear scene value.
vec3 allenwp_curve(vec3 x) {
	const float output_max_value = 1.0; // SDR always has an output_max_value of 1.0

	// These constants must match the those in the C++ code that calculates the parameters.
	// 18% "middle gray" is perceptually 50% of the brightness of reference white.
	const float awp_crossover_point = 0.18;
	// When output_max_value and/or awp_crossover_point are no longer constant,
	// awp_shoulder_max can be calculated on the CPU and passed in as tonemap_e.
	const float awp_shoulder_max = output_max_value - awp_crossover_point;

	float awp_contrast = tonemapper_params.x;
	float awp_toe_a = tonemapper_params.y;
	float awp_slope = tonemapper_params.z;
	float awp_w = tonemapper_params.w;

	// Reinhard-like shoulder:
	vec3 s = x - awp_crossover_point;
	vec3 slope_s = awp_slope * s;
	s = slope_s * (1.0 + s / awp_w) / (1.0 + (slope_s / awp_shoulder_max));
	s += awp_crossover_point;

	// Sigmoid power function toe:
	vec3 t = pow(x, vec3(awp_contrast));
	t = t / (t + awp_toe_a);

	return mix(s, t, lessThan(x, vec3(awp_crossover_point)));
}

// This is an approximation and simplification of EaryChow's AgX implementation that is used by Blender.
// This code is based off of the script that generates the AgX_Base_sRGB.cube LUT that Blender uses.
// Source: https://github.com/EaryChow/AgX_LUT_Gen/blob/main/AgXBasesRGB.py
// Colorspace transformation source: https://www.colour-science.org:8010/apps/rgb_colourspace_transformation_matrix
vec3 tonemap_agx(vec3 color) {
	// Input color should be non-negative!
	// Large negative values in one channel and large positive values in other
	// channels can result in a colour that appears darker and more saturated than
	// desired after passing it through the inset matrix. For this reason, it is
	// best to prevent negative input values.
	// This is done before the Rec. 2020 transform to allow the Rec. 2020
	// transform to be combined with the AgX inset matrix. This results in a loss
	// of color information that could be correctly interpreted within the
	// Rec. 2020 color space as positive RGB values, but is often not worth
	// the performance cost of an additional matrix multiplication.
	//
	// Additionally, this AgX configuration was created subjectively based on
	// output appearance in the Rec. 709 color gamut, so it is possible that these
	// matrices will not perform well with non-Rec. 709 output (more testing with
	// future wide-gamut displays is be needed).
	// See this comment from the author on the decisions made to create the matrices:
	// https://github.com/godotengine/godot-proposals/issues/12317#issuecomment-2835824250

	// Combined Rec. 709 to Rec. 2020 and Blender AgX inset matrices:
	const mat3 rec709_to_rec2020_agx_inset_matrix = mat3(
			0.544814746488245, 0.140416948464053, 0.0888104196149096,
			0.373787398372697, 0.754137554567394, 0.178871756420858,
			0.0813978551390581, 0.105445496968552, 0.732317823964232);

	// Combined inverse AgX outset matrix and Rec. 2020 to Rec. 709 matrices.
	const mat3 agx_outset_rec2020_to_rec709_matrix = mat3(
			1.96488741169489, -0.299313364904742, -0.164352742528393,
			-0.855988495690215, 1.32639796461980, -0.238183969428088,
			-0.108898916004672, -0.0270845997150571, 1.40253671195648);

	const float output_max_value = 1.0; // SDR always has an output_max_value of 1.0

	// Apply inset matrix.
	color = rec709_to_rec2020_agx_inset_matrix * color;

	// Use the allenwp tonemapping curve to match the Blender AgX curve while
	// providing stability across all variable dyanimc range (SDR, HDR, EDR).
	color = allenwp_curve(color);

	// Clipping to output_max_value is required to address a cyan colour that occurs
	// with very bright inputs.
	color = min(vec3(output_max_value), color);

	// Apply outset to make the result more chroma-laden and then go back to Rec. 709.
	color = agx_outset_rec2020_to_rec709_matrix * color;

	// Blender's lusRGB.compensate_low_side is too complex for this shader, so
	// simply return the color, even if it has negative components. These negative
	// components may be useful for subsequent color adjustments.
	return color;
}

#define TONEMAPPER_LINEAR 0
#define TONEMAPPER_REINHARD 1
#define TONEMAPPER_FILMIC 2
#define TONEMAPPER_ACES 3
#define TONEMAPPER_AGX 4

vec3 apply_tonemapping(vec3 color) { // inputs are LINEAR
	if (tonemapper == TONEMAPPER_LINEAR) {
		return color;
	}

	// Ensure color values passed to tonemappers are positive.
	// They can be negative in the case of negative lights, which leads to undesired behavior.
	color = max(vec3(0.0), color);

	if (tonemapper == TONEMAPPER_REINHARD) {
		return tonemap_reinhard(color);
	} else if (tonemapper == TONEMAPPER_FILMIC) {
		return tonemap_filmic(color);
	} else if (tonemapper == TONEMAPPER_ACES) {
		return tonemap_aces(color);
	} else { // TONEMAPPER_AGX
		return tonemap_agx(color);
	}
}

#endif // APPLY_TONEMAPPING

in vec2 uv_interp;

/* clang-format on */

uniform samplerCube radiance; //texunit:-2
#ifdef USE_CUBEMAP_PASS
uniform samplerCube half_res; //texunit:-2
uniform samplerCube quarter_res; //texunit:-3
#elif defined(USE_MULTIVIEW)
uniform sampler2DArray half_res; //texunit:-2
uniform sampler2DArray quarter_res; //texunit:-3
#else
uniform sampler2D half_res; //texunit:-2
uniform sampler2D quarter_res; //texunit:-3
#endif

layout(std140) uniform GlobalShaderUniformData { //ubo:1
	vec4 global_shader_uniforms[MAX_GLOBAL_SHADER_UNIFORMS];
};

struct DirectionalLightData {
	vec4 direction_energy;
	vec4 color_size;
	uint enabled_bake_mode;
	float shadow_opacity;
	float specular;
	uint mask;
};

layout(std140) uniform DirectionalLights { //ubo:4
	DirectionalLightData data[MAX_DIRECTIONAL_LIGHT_DATA_STRUCTS];
}
directional_lights;

#define DIRECTIONAL_LIGHT_ENABLED uint(1 << 0)

// mat4 is a waste of space, but we don't have an easy way to set a mat3 uniform for now
uniform mat4 orientation;
uniform vec4 projection;
uniform vec3 position;
uniform float time;
uniform float sky_energy_multiplier;
uniform float luminance_multiplier;

uniform float fog_aerial_perspective;
uniform vec4 fog_light_color;
uniform float fog_sun_scatter;
uniform bool fog_enabled;
uniform float fog_density;
uniform float fog_sky_affect;
uniform uint directional_light_count;

/* clang-format off */

#ifdef MATERIAL_UNIFORMS_USED
layout(std140) uniform MaterialUniforms{ //ubo:3

#MATERIAL_UNIFORMS

};
#endif
/* clang-format on */
#GLOBALS

#ifdef USE_CUBEMAP_PASS
#define AT_CUBEMAP_PASS true
#else
#define AT_CUBEMAP_PASS false
#endif

#ifdef USE_HALF_RES_PASS
#define AT_HALF_RES_PASS true
#else
#define AT_HALF_RES_PASS false
#endif

#ifdef USE_QUARTER_RES_PASS
#define AT_QUARTER_RES_PASS true
#else
#define AT_QUARTER_RES_PASS false
#endif

#ifdef USE_MULTIVIEW
layout(std140) uniform MultiviewData { // ubo:12
	highp mat4 projection_matrix_view[MAX_VIEWS];
	highp mat4 inv_projection_matrix_view[MAX_VIEWS];
	highp vec4 eye_offset[MAX_VIEWS];
}
multiview_data;
#endif

layout(location = 0) out vec4 frag_color;

#ifdef USE_DEBANDING
// https://www.iryoku.com/next-generation-post-processing-in-call-of-duty-advanced-warfare
vec3 interleaved_gradient_noise(vec2 pos) {
	const vec3 magic = vec3(0.06711056f, 0.00583715f, 52.9829189f);
	float res = fract(magic.z * fract(dot(pos, magic.xy))) * 2.0 - 1.0;
	return vec3(res, -res, res) / 255.0;
}
#endif

#if !defined(DISABLE_FOG)
vec4 fog_process(vec3 view, vec3 sky_color) {
	vec3 fog_color = mix(fog_light_color.rgb, sky_color, fog_aerial_perspective);

	if (fog_sun_scatter > 0.001) {
		vec4 sun_scatter = vec4(0.0);
		float sun_total = 0.0;
		for (uint i = 0u; i < directional_light_count; i++) {
			vec3 light_color = srgb_to_linear(directional_lights.data[i].color_size.xyz) * directional_lights.data[i].direction_energy.w;
			float light_amount = pow(max(dot(view, directional_lights.data[i].direction_energy.xyz), 0.0), 8.0) * M_PI;
			fog_color += light_color * light_amount * fog_sun_scatter;
		}
	}

	return vec4(fog_color, 1.0);
}
#endif // !DISABLE_FOG

// Eberly approximations from https://seblagarde.wordpress.com/2014/12/01/inverse-trigonometric-functions-gpu-optimization-for-amd-gcn-architecture/.
// input [-1, 1] and output [0, PI]
float acos_approx(float p_x) {
	float x = abs(p_x);
	float res = -0.156583f * x + (M_PI / 2.0);
	res *= sqrt(1.0f - x);
	return (p_x >= 0.0) ? res : M_PI - res;
}

// Based on https://math.stackexchange.com/questions/1098487/atan2-faster-approximation
// but using the Eberly coefficients from https://seblagarde.wordpress.com/2014/12/01/inverse-trigonometric-functions-gpu-optimization-for-amd-gcn-architecture/.
float atan2_approx(float y, float x) {
	float a = min(abs(x), abs(y)) / max(abs(x), abs(y));
	float s = a * a;
	float poly = 0.0872929f;
	poly = -0.301895f + poly * s;
	poly = 1.0f + poly * s;
	poly = poly * a;

	float r = abs(y) > abs(x) ? (M_PI / 2.0) - poly : poly;
	r = x < 0.0 ? M_PI - r : r;
	r = y < 0.0 ? -r : r;

	return r;
}

void main() {
	vec3 cube_normal;
#ifdef USE_MULTIVIEW
	// In multiview our projection matrices will contain positional and rotational offsets that we need to properly unproject.
	vec4 unproject = vec4(uv_interp.xy, -1.0, 1.0); // unproject at the far plane
	vec4 unprojected = multiview_data.inv_projection_matrix_view[ViewIndex] * unproject;
	cube_normal = unprojected.xyz / unprojected.w;

	// Unproject will give us the position between the eyes, need to re-offset.
	cube_normal += multiview_data.eye_offset[ViewIndex].xyz;
#else
	cube_normal.z = -1.0;
	cube_normal.x = (uv_interp.x + projection.x) / projection.y;
	cube_normal.y = (uv_interp.y + projection.z) / projection.w;
#endif
	cube_normal = mat3(orientation) * cube_normal;
	cube_normal = normalize(cube_normal);

	vec2 uv = uv_interp * 0.5 + 0.5;

	vec2 panorama_coords = vec2(atan2_approx(cube_normal.x, -cube_normal.z), acos_approx(cube_normal.y));

	if (panorama_coords.x < 0.0) {
		panorama_coords.x += M_PI * 2.0;
	}

	panorama_coords /= vec2(M_PI * 2.0, M_PI);

	vec3 color = vec3(0.0, 0.0, 0.0);
	float alpha = 1.0; // Only available to subpasses
	vec4 half_res_color = vec4(1.0);
	vec4 quarter_res_color = vec4(1.0);
	vec4 custom_fog = vec4(0.0);

#ifdef USE_CUBEMAP_PASS
#ifdef USES_HALF_RES_COLOR
	half_res_color = texture(half_res, cube_normal);
#endif
#ifdef USES_QUARTER_RES_COLOR
	quarter_res_color = texture(quarter_res, cube_normal);
#endif
#else
#ifdef USES_HALF_RES_COLOR
#ifdef USE_MULTIVIEW
	half_res_color = textureLod(half_res, vec3(uv, ViewIndex), 0.0);
#else
	half_res_color = textureLod(half_res, uv, 0.0);
#endif
#endif
#ifdef USES_QUARTER_RES_COLOR
#ifdef USE_MULTIVIEW
	quarter_res_color = textureLod(quarter_res, vec3(uv, ViewIndex), 0.0);
#else
	quarter_res_color = textureLod(quarter_res, uv, 0.0);
#endif
#endif
#endif

	{
#CODE : SKY
	}

	// Convert to Linear for tonemapping so color matches scene shader better
	color = srgb_to_linear(color);

	color *= sky_energy_multiplier;

#if !defined(DISABLE_FOG)

	// Draw "fixed" fog before volumetric fog to ensure volumetric fog can appear in front of the sky.
	if (fog_enabled) {
		vec4 fog = fog_process(cube_normal, color.rgb);
		color.rgb = mix(color.rgb, fog.rgb, fog.a * fog_sky_affect);
	}

	if (custom_fog.a > 0.0) {
		color.rgb = mix(color.rgb, custom_fog.rgb, custom_fog.a);
	}

#endif // DISABLE_FOG

	color *= exposure;
#ifdef APPLY_TONEMAPPING
	color = apply_tonemapping(color);
#endif
	color = linear_to_srgb(color);

	frag_color.rgb = color * luminance_multiplier;
	frag_color.a = alpha;

#ifdef USE_DEBANDING
	frag_color.rgb += interleaved_gradient_noise(gl_FragCoord.xy) * sky_energy_multiplier * luminance_multiplier;
#endif
}
)<!>"
		};

		_setup(_vertex_code, _fragment_code, "SkyShaderGLES3",
				14, _uniform_strings, 5, _ubo_pairs,
				0, _feedbacks, 3, _texunit_pairs,
				5, _spec_pairs, 2, _variant_defines);
	}
};
