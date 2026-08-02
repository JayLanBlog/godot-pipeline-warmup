/**************************************************************************/
/*  pipeline_warmup_rd.h                                                  */
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

#pragma once

#include "core/object/object.h"
#include "core/string/ustring.h"
#include "core/templates/hash_map.h"
#include "core/variant/callable.h"
#include "core/variant/variant.h"
#include "servers/rendering/rendering_server_enums.h"

class PipelineWarmupRD {
public:
	struct WarmupEntry {
		// High-level identification (from manifest).
		String material;
		String shader;
		String vertex_format;
		HashMap<String, bool> features;

		// PipelineKey fields (optional, default to 0/"unknown").
		uint64_t vertex_format_id = 0;
		uint64_t framebuffer_format_id = 0;
		int cull_mode = -1; // -1 = use shader default, otherwise RD::PolygonCullMode
		int primitive_type = RSE::PRIMITIVE_TRIANGLES;
		int pipeline_version = -1; // -1 = iterate all versions
		uint32_t color_pass_flags = 0;
		uint32_t specialization_packed_0 = 0;
		uint32_t specialization_packed_1 = 0;
		uint32_t specialization_packed_2 = 0;
		uint32_t wireframe = 0;
		uint32_t ubershader = 0;

		uint32_t get_features_hash() const;
		String get_dedupe_key() const;
	};

	using CompileCallback = Callable;
	using DiscoverCallback = Callable;

private:
	static PipelineWarmupRD *singleton;

	Vector<CompileCallback> providers;
	Vector<DiscoverCallback> discoverers;

	Vector<WarmupEntry> entries;
	Vector<WarmupEntry> runtime_collected;
	Mutex runtime_collected_mutex;
	int submitted_count = 0;
	int completed_count = 0;
	float max_seconds = 5.0f;
	bool active = false;
	bool finished_flag = true;
	float elapsed_seconds = 0.0f;
	int total_entries = 0;
	int compiled_entries = 0;
	bool timed_out = false;

	void _parse_manifest_json(const String &p_path, const String &p_source_name, Vector<WarmupEntry> &r_entries);
	void _merge_and_dedupe();
	void _load_manifests();
	void _submit_entries();
	void _save_runtime_cache();

public:
	static PipelineWarmupRD *get_singleton() { return singleton; }

	PipelineWarmupRD();
	~PipelineWarmupRD();

	void register_provider(const CompileCallback &p_callback);

	// Register a discover callback for fallback when no manifest entries exist.
	void register_discoverer(const DiscoverCallback &p_callback);

	// Called by renderers during normal rendering when a pipeline is compiled.
	// Records the entry for inclusion in the next runtime cache save.
	void add_runtime_entry(const Dictionary &p_entry);

	// Called at engine shutdown to persist runtime-collected entries.
	void save_runtime_cache_on_shutdown();

	void warmup();
	float get_progress() const;
	bool is_finished() const;

	void set_max_seconds(float p_seconds);
	float get_max_seconds() const { return max_seconds; }

	int get_total_entries() const { return total_entries; }
	int get_compiled_entries() const { return compiled_entries; }
	float get_elapsed_seconds() const { return elapsed_seconds; }
	bool get_timed_out() const { return timed_out; }
};