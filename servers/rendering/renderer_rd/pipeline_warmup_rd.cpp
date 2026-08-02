/**************************************************************************/
/*  pipeline_warmup_rd.cpp                                                */
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

#include "pipeline_warmup_rd.h"

#include "core/config/project_settings.h"
#include "core/io/file_access.h"
#include "core/io/json.h"
#include "core/os/os.h"
#include "core/string/print_string.h"
#include "core/templates/hash_set.h"
#include "servers/rendering/rendering_server.h"

PipelineWarmupRD *PipelineWarmupRD::singleton = nullptr;

// ============================================================
// WarmupEntry
// ============================================================

uint32_t PipelineWarmupRD::WarmupEntry::get_features_hash() const {
	// Build a deterministic string from features for hashing.
	// Sort keys to guarantee consistent order across different HashMap instances.
	LocalVector<String> keys;
	for (const KeyValue<String, bool> &kv : features) {
		keys.push_back(kv.key);
	}
	keys.sort();
	String features_str;
	for (const String &key : keys) {
		features_str += key + "=" + (features[key] ? "1" : "0") + ";";
	}
	return features_str.hash();
}

String PipelineWarmupRD::WarmupEntry::get_dedupe_key() const {
	// Include pipeline key fields to distinguish different pipeline variants of the same shader.
	return material + "|" + vertex_format + "|" + itos(get_features_hash()) +
			"|vf=" + itos(vertex_format_id) +
			"|fb=" + itos(framebuffer_format_id) +
			"|cm=" + itos(cull_mode) +
			"|pt=" + itos(primitive_type) +
			"|pv=" + itos(pipeline_version) +
			"|cpf=" + itos(color_pass_flags) +
			"|sp0=" + itos(specialization_packed_0) +
			"|sp1=" + itos(specialization_packed_1) +
			"|sp2=" + itos(specialization_packed_2) +
			"|ub=" + itos(ubershader) +
			"|wf=" + itos(wireframe);
}

// ============================================================
// PipelineWarmupRD
// ============================================================

PipelineWarmupRD::PipelineWarmupRD() {
	singleton = this;
}

PipelineWarmupRD::~PipelineWarmupRD() {
	// Do NOT call _save_runtime_cache() here — the destructor runs during
	// RenderingServerDefault::_finish() where the file system may be partially
	// shut down. Saving is handled by save_runtime_cache_on_shutdown() which
	// is called explicitly before memdelete.
	singleton = nullptr;
}

void PipelineWarmupRD::register_provider(const CompileCallback &p_callback) {
	providers.push_back(p_callback);
}

void PipelineWarmupRD::register_discoverer(const DiscoverCallback &p_callback) {
	discoverers.push_back(p_callback);
}

void PipelineWarmupRD::add_runtime_entry(const Dictionary &p_entry) {
	WarmupEntry we;
	we.material = p_entry.get("material", "");
	we.shader = p_entry.get("shader", "");
	we.vertex_format = p_entry.get("vertex_format", "unknown");

	Dictionary features_dict = p_entry.get("features", Dictionary());
	LocalVector<Variant> feature_keys = features_dict.get_key_list();
	for (const Variant &key : feature_keys) {
		we.features[key] = features_dict[key];
	}

	we.vertex_format_id = uint64_t(p_entry.get("vertex_format_id", 0));
	we.framebuffer_format_id = uint64_t(p_entry.get("framebuffer_format_id", 0));
	we.cull_mode = int(p_entry.get("cull_mode", -1));
	we.primitive_type = int(p_entry.get("primitive_type", RSE::PRIMITIVE_TRIANGLES));
	we.pipeline_version = int(p_entry.get("pipeline_version", -1));
	we.color_pass_flags = uint32_t(int(p_entry.get("color_pass_flags", 0)));
	we.specialization_packed_0 = uint32_t(int(p_entry.get("specialization_packed_0", 0)));
	we.specialization_packed_1 = uint32_t(int(p_entry.get("specialization_packed_1", 0)));
	we.specialization_packed_2 = uint32_t(int(p_entry.get("specialization_packed_2", 0)));
	we.wireframe = uint32_t(int(p_entry.get("wireframe", 0)));
	we.ubershader = uint32_t(int(p_entry.get("ubershader", 0)));

	MutexLock lock(runtime_collected_mutex);
	runtime_collected.push_back(we);
}

void PipelineWarmupRD::save_runtime_cache_on_shutdown() {
	print_line(vformat("[PipelineWarmup] Shutdown: runtime_collected size=%d, entries size=%d",
			runtime_collected.size(), entries.size()));
	{
		MutexLock lock(runtime_collected_mutex);
		_save_runtime_cache();
	}
}

void PipelineWarmupRD::set_max_seconds(float p_seconds) {
	max_seconds = p_seconds;
}

float PipelineWarmupRD::get_progress() const {
	if (total_entries == 0) {
		return finished_flag ? 1.0f : 0.0f;
	}
	return float(completed_count) / float(total_entries);
}

bool PipelineWarmupRD::is_finished() const {
	return finished_flag;
}

void PipelineWarmupRD::_parse_manifest_json(const String &p_path, const String &p_source_name, Vector<WarmupEntry> &r_entries) {
	Ref<FileAccess> f = FileAccess::open(p_path, FileAccess::READ);
	if (f.is_null()) {
		// File not found — silently skip
		return;
	}

	String json_text = f->get_as_utf8_string();
	if (json_text.is_empty()) {
		print_line("[PipelineWarmup] Manifest file is empty: " + p_path);
		return;
	}

	Variant parsed = JSON::parse_string(json_text);
	if (parsed.get_type() != Variant::DICTIONARY) {
		print_line("[PipelineWarmup] Failed to parse manifest JSON: " + p_path);
		return;
	}

	Dictionary root = parsed;
	int version = root.get("version", 0);
	if (version != 2) {
		print_line("[PipelineWarmup] Unsupported manifest version " + itos(version) + " in: " + p_path);
		return;
	}

	Array pipelines = root.get("pipelines", Array());
	int added = 0;
	int skipped = 0;

	for (int i = 0; i < pipelines.size(); i++) {
		Dictionary entry = pipelines[i];
		String material = entry.get("material", "");
		String shader = entry.get("shader", "");

		if (material.is_empty() || shader.is_empty()) {
			skipped++;
			continue;
		}

		WarmupEntry we;
		we.material = material;
		we.shader = shader;
		we.vertex_format = entry.get("vertex_format", "unknown");

		Dictionary features_dict = entry.get("features", Dictionary());
		LocalVector<Variant> feature_keys = features_dict.get_key_list();
		for (const Variant &key : feature_keys) {
			we.features[key] = features_dict[key];
		}

		// PipelineKey fields (optional, for detailed warmup).
		we.vertex_format_id = uint64_t(entry.get("vertex_format_id", 0));
		we.framebuffer_format_id = uint64_t(entry.get("framebuffer_format_id", 0));
		we.cull_mode = int(entry.get("cull_mode", -1));
		we.primitive_type = int(entry.get("primitive_type", RSE::PRIMITIVE_TRIANGLES));
		we.pipeline_version = int(entry.get("pipeline_version", -1));
		we.color_pass_flags = uint32_t(int(entry.get("color_pass_flags", 0)));
		we.specialization_packed_0 = uint32_t(int(entry.get("specialization_packed_0", 0)));
		we.specialization_packed_1 = uint32_t(int(entry.get("specialization_packed_1", 0)));
		we.specialization_packed_2 = uint32_t(int(entry.get("specialization_packed_2", 0)));
		we.wireframe = uint32_t(int(entry.get("wireframe", 0)));
		we.ubershader = uint32_t(int(entry.get("ubershader", 0)));

		r_entries.push_back(we);
		added++;
	}

	print_line(vformat("[PipelineWarmup] Loaded %s from %s: %d entries (%d skipped)",
			p_source_name, p_path, added, skipped));
}

void PipelineWarmupRD::_merge_and_dedupe() {
	HashSet<String> seen_keys;
	Vector<WarmupEntry> merged;

	for (const WarmupEntry &entry : entries) {
		String key = entry.get_dedupe_key();
		if (seen_keys.has(key)) {
			continue;
		}
		seen_keys.insert(key);
		merged.push_back(entry);
	}

	int duplicates = entries.size() - merged.size();
	entries = merged;

	print_line(vformat("[PipelineWarmup] After deduplication: %d entries (%d duplicates removed)",
			entries.size(), duplicates));
}

void PipelineWarmupRD::_load_manifests() {
	entries.clear();

	// Priority 1: Editor exported manifest (highest priority)
	if (GLOBAL_GET("rendering/pipeline_warmup/use_imported_manifest")) {
		String manifest_path = GLOBAL_GET("rendering/pipeline_warmup/manifest_path");
		_parse_manifest_json(manifest_path, "editor_export", entries);
	}

	// Priority 2: Import auto-generated manifest
	if (GLOBAL_GET("rendering/pipeline_warmup/use_imported_manifest")) {
		_parse_manifest_json("res://.godot/imported_pipelines.json", "import", entries);
	}

	// Priority 3: Runtime incremental cache
	if (GLOBAL_GET("rendering/pipeline_warmup/use_runtime_cache")) {
		_parse_manifest_json("user://pipeline_warmup_cache.json", "runtime_cache", entries);
	}

	_merge_and_dedupe();
}

void PipelineWarmupRD::_submit_entries() {
	for (const WarmupEntry &entry : entries) {
		Dictionary entry_dict;
		entry_dict["material"] = entry.material;
		entry_dict["shader"] = entry.shader;
		entry_dict["vertex_format"] = entry.vertex_format;

		Dictionary features_dict;
		for (const KeyValue<String, bool> &kv : entry.features) {
			features_dict[kv.key] = kv.value;
		}
		entry_dict["features"] = features_dict;

		// PipelineKey fields.
		entry_dict["vertex_format_id"] = entry.vertex_format_id;
		entry_dict["framebuffer_format_id"] = entry.framebuffer_format_id;
		entry_dict["cull_mode"] = entry.cull_mode;
		entry_dict["primitive_type"] = entry.primitive_type;
		entry_dict["pipeline_version"] = entry.pipeline_version;
		entry_dict["color_pass_flags"] = entry.color_pass_flags;
		entry_dict["specialization_packed_0"] = entry.specialization_packed_0;
		entry_dict["specialization_packed_1"] = entry.specialization_packed_1;
		entry_dict["specialization_packed_2"] = entry.specialization_packed_2;
		entry_dict["wireframe"] = entry.wireframe;
		entry_dict["ubershader"] = entry.ubershader;

		Variant entry_variant = entry_dict;
		const Variant *args[1] = { &entry_variant };

		for (const CompileCallback &cb : providers) {
			Variant ret;
			Callable::CallError error;
			cb.callp(args, 1, ret, error);
		}
		submitted_count++;
		completed_count++;
	}
}

void PipelineWarmupRD::_save_runtime_cache() {
	if (!GLOBAL_GET("rendering/pipeline_warmup/use_runtime_cache")) {
		return;
	}

	// Merge warmup entries and runtime-collected entries with deduplication.
	// Use seen_keys to avoid duplicates.
	HashSet<String> seen_keys;
	Vector<WarmupEntry> merged;
	auto append_unique = [&](const WarmupEntry &we) {
		String key = we.get_dedupe_key();
		if (!seen_keys.has(key)) {
			seen_keys.insert(key);
			merged.push_back(we);
		}
	};
	for (const WarmupEntry &we : entries) {
		append_unique(we);
	}
	int new_runtime_count = 0;
	{
		MutexLock lock(runtime_collected_mutex);
		for (const WarmupEntry &we : runtime_collected) {
			String key = we.get_dedupe_key();
			if (!seen_keys.has(key)) {
				new_runtime_count++;
			}
			append_unique(we);
		}
	}

	// Build JSON.
	Dictionary root;
	root["version"] = 2;

	OS::DateTime dt = OS::get_singleton()->get_datetime();
	String timestamp = vformat("%04d-%02d-%02dT%02d:%02d:%02d",
			int64_t(dt.year), int(dt.month), dt.day,
			dt.hour, dt.minute, dt.second);
	root["updated_at"] = timestamp;

	String device = RenderingServer::get_singleton()->get_video_adapter_name().to_lower().replace(" ", "_");
	root["device"] = device;

	Array pipelines;
	for (const WarmupEntry &entry : merged) {
		Dictionary d;
		d["material"] = entry.material;
		d["shader"] = entry.shader;
		d["vertex_format"] = entry.vertex_format;

		Dictionary features_dict;
		for (const KeyValue<String, bool> &kv : entry.features) {
			features_dict[kv.key] = kv.value;
		}
		d["features"] = features_dict;

		d["vertex_format_id"] = entry.vertex_format_id;
		d["framebuffer_format_id"] = entry.framebuffer_format_id;
		d["cull_mode"] = entry.cull_mode;
		d["primitive_type"] = entry.primitive_type;
		d["pipeline_version"] = entry.pipeline_version;
		d["color_pass_flags"] = entry.color_pass_flags;
		d["specialization_packed_0"] = entry.specialization_packed_0;
		d["specialization_packed_1"] = entry.specialization_packed_1;
		d["specialization_packed_2"] = entry.specialization_packed_2;
		d["wireframe"] = entry.wireframe;
		d["ubershader"] = entry.ubershader;

		pipelines.push_back(d);
	}
	root["pipelines"] = pipelines;

	String json_text = JSON::stringify(root, "  ");
	Ref<FileAccess> f = FileAccess::open("user://pipeline_warmup_cache.json", FileAccess::WRITE);
	if (f.is_valid()) {
		f->store_string(json_text);
		f->close();
		print_line(vformat("[PipelineWarmup] Saved runtime cache: %d entries (%d new from runtime) to user://pipeline_warmup_cache.json",
				pipelines.size(), new_runtime_count));
	} else {
		print_line("[PipelineWarmup] Failed to save runtime cache");
	}
}

void PipelineWarmupRD::warmup() {
	if (active) {
		print_line("[PipelineWarmup] Warmup already in progress, ignoring");
		return;
	}

	if (providers.is_empty()) {
		print_line("[PipelineWarmup] No providers registered, skipping warmup");
		finished_flag = true;
		return;
	}

	active = true;
	finished_flag = false;
	submitted_count = 0;
	completed_count = 0;
	timed_out = false;

	uint64_t start_ticks = OS::get_singleton()->get_ticks_msec();

	// Load manifest entries
	_load_manifests();

	total_entries = entries.size();
	compiled_entries = 0;

	if (total_entries == 0) {
		// No manifest entries — try discovery fallback.
		if (!discoverers.is_empty()) {
			print_line("[PipelineWarmup] No manifest entries found, running discovery fallback...");
			for (const DiscoverCallback &dc : discoverers) {
				Variant ret;
				Callable::CallError error;
				dc.callp(nullptr, 0, ret, error);
			}
		} else {
			print_line("[PipelineWarmup] No entries to warm up (no manifest entries and no discoverers)");
		}
		elapsed_seconds = 0.0f;
		_save_runtime_cache();
		finished_flag = true;
		active = false;
		return;
	}

	print_line(vformat("[PipelineWarmup] Starting warmup with %d entries...", total_entries));

	// Submit entries, respecting timeout.
	// Temporarily limit entries to only those within the time budget.
	float max_seconds_f = GLOBAL_GET("rendering/pipeline_warmup/max_seconds");
	Vector<WarmupEntry> budgeted_entries;
	for (int i = 0; i < entries.size(); i++) {
		uint64_t elapsed_ms = OS::get_singleton()->get_ticks_msec() - start_ticks;
		if (elapsed_ms >= uint64_t(max_seconds_f * 1000.0f)) {
			timed_out = true;
			print_line(vformat("[PipelineWarmup] Timeout reached after %.2fs, stopping submission (%d/%d submitted)",
					elapsed_ms / 1000.0f, submitted_count, total_entries));
			break;
		}
		budgeted_entries.push_back(entries[i]);
	}

	// Swap and submit.
	Vector<WarmupEntry> saved_entries = entries;
	entries = budgeted_entries;
	_submit_entries();
	entries = saved_entries;

	compiled_entries = submitted_count;

	uint64_t end_ticks = OS::get_singleton()->get_ticks_msec();
	elapsed_seconds = (end_ticks - start_ticks) / 1000.0f;

	print_line(vformat("[PipelineWarmup] Finished: compiled %d/%d entries in %.2fs (timed out: %s, skipped: %d)",
			compiled_entries, total_entries, elapsed_seconds,
			timed_out ? "true" : "false",
			total_entries - submitted_count));

	// Also save entries that were collected during warmup's async compilations.
	_save_runtime_cache();

	finished_flag = true;
	active = false;
}