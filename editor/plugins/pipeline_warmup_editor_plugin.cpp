/**************************************************************************/
/*  pipeline_warmup_editor_plugin.cpp                                     */
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
/* SOFTWARE OR THE USE OF OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "pipeline_warmup_editor_plugin.h"

#include "core/config/project_settings.h"
#include "core/io/file_access.h"
#include "core/io/json.h"
#include "core/io/resource_loader.h"
#include "core/object/callable_mp.h"
#include "core/os/os.h"
#include "editor/editor_node.h"
#include "editor/file_system/editor_file_system.h"
#include "scene/3d/mesh_instance_3d.h"
#include "scene/resources/material.h"
#include "scene/resources/mesh.h"
#include "scene/resources/packed_scene.h"
#include "scene/resources/shader.h"

// ARRAY_FORMAT bits (from servers/rendering/rendering_server_enums.h).
// Duplicated here to avoid pulling in heavy rendering server headers.
static const uint64_t AF_VERTEX = 1ULL << 0;
static const uint64_t AF_NORMAL = 1ULL << 1;
static const uint64_t AF_TANGENT = 1ULL << 2;
static const uint64_t AF_COLOR = 1ULL << 3;
static const uint64_t AF_TEX_UV = 1ULL << 4;
static const uint64_t AF_TEX_UV2 = 1ULL << 5;
static const uint64_t AF_BONES = 1ULL << 9;
static const uint64_t AF_WEIGHTS = 1ULL << 10;

static void _scan_efs_directory(EditorFileSystemDirectory *p_dir, Vector<String> &r_files) {
	for (int i = 0; i < p_dir->get_file_count(); i++) {
		if (p_dir->get_file_type(i) == SNAME("PackedScene")) {
			r_files.push_back(p_dir->get_file_path(i));
		}
	}
	for (int i = 0; i < p_dir->get_subdir_count(); i++) {
		_scan_efs_directory(p_dir->get_subdir(i), r_files);
	}
}

String PipelineWarmupEditorPlugin::PipelineEntry::get_dedupe_key() const {
	return material + "|" + shader + "|" + vertex_format;
}

String PipelineWarmupEditorPlugin::_format_mask_to_string(uint64_t p_mask) {
	String result;
	if (p_mask & AF_VERTEX) {
		result += "pos";
	}
	if (p_mask & AF_NORMAL) {
		if (!result.is_empty()) result += "-";
		result += "norm";
	}
	if (p_mask & AF_TANGENT) {
		if (!result.is_empty()) result += "-";
		result += "tangent";
	}
	if (p_mask & AF_COLOR) {
		if (!result.is_empty()) result += "-";
		result += "color";
	}
	if (p_mask & AF_TEX_UV) {
		if (!result.is_empty()) result += "-";
		result += "uv";
	}
	if (p_mask & AF_TEX_UV2) {
		if (!result.is_empty()) result += "-";
		result += "uv2";
	}
	if (p_mask & AF_BONES) {
		if (!result.is_empty()) result += "-";
		result += "bones";
	}
	if (p_mask & AF_WEIGHTS) {
		if (!result.is_empty()) result += "-";
		result += "weights";
	}
	return result.is_empty() ? "unknown" : result;
}

void PipelineWarmupEditorPlugin::_extract_from_node(Node *p_node) {
	MeshInstance3D *mi = Object::cast_to<MeshInstance3D>(p_node);
	if (!mi) {
		return;
	}

	Ref<Mesh> mesh = mi->get_mesh();
	if (mesh.is_null()) {
		return;
	}

	int surface_count = mesh->get_surface_count();
	for (int s = 0; s < surface_count; s++) {
		Ref<Material> material = mi->get_active_material(s);
		if (material.is_null()) {
			continue;
		}

		// Get shader path — only ShaderMaterial exposes get_shader().
		ShaderMaterial *sm = Object::cast_to<ShaderMaterial>(material.ptr());
		String shader_path;
		if (sm) {
			Ref<Shader> shader = sm->get_shader();
			if (shader.is_valid()) {
				shader_path = shader->get_path();
			}
		}
		if (shader_path.is_empty()) {
			// Built-in shader — use mode name as identifier.
			switch (material->get_shader_mode()) {
				case Shader::MODE_SPATIAL:
					shader_path = "builtin://spatial";
					break;
				case Shader::MODE_CANVAS_ITEM:
					shader_path = "builtin://canvas_item";
					break;
				case Shader::MODE_PARTICLES:
					shader_path = "builtin://particles";
					break;
				case Shader::MODE_SKY:
					shader_path = "builtin://sky";
					break;
				case Shader::MODE_FOG:
					shader_path = "builtin://fog";
					break;
				default:
					continue; // Unknown mode, skip.
			}
		}

		// Determine vertex format from mesh surface.
		uint64_t format_mask = mesh->surface_get_format(s);
		String vertex_format = _format_mask_to_string(format_mask);

		// Detect features from vertex format.
		HashMap<String, bool> features;
		features["skinning"] = (format_mask & AF_BONES) != 0;
		features["has_color"] = (format_mask & AF_COLOR) != 0;
		features["has_uv2"] = (format_mask & AF_TEX_UV2) != 0;

		PipelineEntry entry;
		entry.material = material->get_path();
		entry.shader = shader_path;
		entry.vertex_format = vertex_format;
		entry.features = features;
		entries.push_back(entry);
	}
}

void PipelineWarmupEditorPlugin::_scan_scene(const String &p_path) {
	Ref<PackedScene> scene = ResourceLoader::load(p_path, "PackedScene");
	if (scene.is_null()) {
		print_line(vformat("[PipelineWarmupExport] Failed to load scene: %s", p_path));
		return;
	}

	Node *root = scene->instantiate();
	if (!root) {
		return;
	}

	// Recursively find all MeshInstance3D nodes.
	TypedArray<Node> children = root->find_children("*", "MeshInstance3D", true, false);
	for (int i = 0; i < children.size(); i++) {
		_extract_from_node(Object::cast_to<Node>(children[i]));
	}

	root->queue_free();
}

void PipelineWarmupEditorPlugin::_export_manifest() {
	processed_materials.clear();
	entries.clear();

	EditorFileSystem *efs = EditorFileSystem::get_singleton();
	ERR_FAIL_NULL(efs);

	// Collect all .tscn files from the project.
	Vector<String> scene_files;
	_scan_efs_directory(efs->get_filesystem(), scene_files);

	print_line(vformat("[PipelineWarmupExport] Found %d scene files to scan", scene_files.size()));

	for (const String &path : scene_files) {
		_scan_scene(path);
	}

	// Deduplicate.
	HashSet<String> seen_keys;
	Vector<PipelineEntry> deduped;
	for (const PipelineEntry &e : entries) {
		String key = e.get_dedupe_key();
		if (seen_keys.has(key)) {
			continue;
		}
		seen_keys.insert(key);
		deduped.push_back(e);
	}
	int duplicates = entries.size() - deduped.size();
	entries = deduped;

	print_line(vformat("[PipelineWarmupExport] Collected %d unique pipeline entries (%d duplicates removed)",
			entries.size(), duplicates));

	// Build JSON.
	Dictionary root;
	root["version"] = 2;
	root["source"] = "editor_export";

	OS::DateTime dt = OS::get_singleton()->get_datetime();
	String timestamp = vformat("%04d-%02d-%02dT%02d:%02d:%02d",
			int64_t(dt.year), int(dt.month), dt.day,
			dt.hour, dt.minute, dt.second);
	root["generated_at"] = timestamp;

	Array pipelines;
	for (const PipelineEntry &e : entries) {
		Dictionary d;
		d["material"] = e.material;
		d["shader"] = e.shader;
		d["vertex_format"] = e.vertex_format;

		Dictionary features_dict;
		for (const KeyValue<String, bool> &kv : e.features) {
			features_dict[kv.key] = kv.value;
		}
		d["features"] = features_dict;

		pipelines.push_back(d);
	}
	root["pipelines"] = pipelines;

	String json_text = JSON::stringify(root, "  ");

	String output_path = GLOBAL_GET("rendering/pipeline_warmup/manifest_path");
	if (output_path.is_empty()) {
		output_path = "res://pipeline_warmup.json";
	}

	Ref<FileAccess> f = FileAccess::open(output_path, FileAccess::WRITE);
	if (f.is_valid()) {
		f->store_string(json_text);
		f->close();
		print_line(vformat("[PipelineWarmupExport] Manifest saved: %d entries to %s",
				entries.size(), output_path));
		EditorNode::get_singleton()->show_warning(
				vformat("Pipeline warmup manifest exported:\n%d entries saved to %s",
						entries.size(), output_path),
				TTR("Export Complete"));
	} else {
		ERR_PRINT(vformat("[PipelineWarmupExport] Failed to write manifest to %s", output_path));
		EditorNode::get_singleton()->show_warning(
				vformat("Failed to write manifest to %s", output_path),
				TTR("Export Error"));
	}
}

PipelineWarmupEditorPlugin::PipelineWarmupEditorPlugin() {
	add_tool_menu_item("Export Pipeline Warmup Manifest...", callable_mp(this, &PipelineWarmupEditorPlugin::_export_manifest));
}
