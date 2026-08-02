/**************************************************************************/
/*  feed.glsl.gen.h                                                       */
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

class FeedShaderGLES3 : public ShaderGLES3 {
public:
	enum ShaderVariant {
		MODE_DEFAULT,
	};

	enum Specializations {
		USE_EXTERNAL_SAMPLER = 1,
	};

	_FORCE_INLINE_ bool version_bind_shader(RID p_version, ShaderVariant p_variant, uint64_t p_specialization = 0) {
		return _version_bind_shader(p_version, p_variant, p_specialization);
	}

protected:
	virtual void _init() override {
		static const char **_uniform_strings = nullptr;
		static const char *_variant_defines[] = {
			"",
		};
		static TexUnitPair _texunit_pairs[] = {
			{ "sourceFeed", 0 },
		};
		static UBOPair *_ubo_pairs = nullptr;
		static Specialization _spec_pairs[] = {
			{ "USE_EXTERNAL_SAMPLER", false },
		};
		static const Feedback *_feedbacks = nullptr;
		static const char _vertex_code[] = {
R"<!>(
layout(location = 0) in vec2 vertex_attrib;

out vec2 uv_interp;


void main() {
	uv_interp = vertex_attrib * 0.5 + 0.5;
	gl_Position = vec4(vertex_attrib, 1.0, 1.0);
}

/* clang-format off */
)<!>"
		};

		static const char _fragment_code[] = {
R"<!>(
layout(location = 0) out vec4 frag_color;
in vec2 uv_interp;

/* clang-format on */
#ifdef USE_EXTERNAL_SAMPLER
uniform samplerExternalOES sourceFeed; // texunit:0
#else
uniform sampler2D sourceFeed; // texunit:0
#endif

void main() {
	vec4 color = texture(sourceFeed, uv_interp);

	frag_color = color;
}
)<!>"
		};

		_setup(_vertex_code, _fragment_code, "FeedShaderGLES3",
				0, _uniform_strings, 0, _ubo_pairs,
				0, _feedbacks, 1, _texunit_pairs,
				1, _spec_pairs, 1, _variant_defines);
	}
};
