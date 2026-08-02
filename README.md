# Native C++ Pipeline Warmup — Godot Engine 集成

> 在 Godot 引擎渲染层实现的原生管线预热，消除首次渲染的 Shader/Pipeline 编译卡顿。  
> 附带 Dense200 压力场景的完整 A/B 对比基准测试。

## 概述

本仓库是 Godot Shader Pipeline Warmup 的测试项目，用于验证 **Native C++ 管线预热**在真实渲染场景中的效果。核心思路：

1. **引擎启动时** — `PipelineWarmupRD` 加载 JSON manifest，直接调用 Vulkan `pipeline_create` 批量预编译
2. **场景运行时** — 800 个独立材质的 MeshInstance3D 逐帧 Reveal，FrameTimeLogger 记录逐帧时间
3. **对比验证** — 同一场景在"无预热 vs 有预热"两种模式下各跑一轮，量化预热收益

## 架构

![Pipeline Warmup 架构总览](../godot/benchmark-comparison/no-warmup-vs-warmup/assets/architecture.png)

*图：Native C++ Pipeline Warmup 架构总览 — Godot Engine 渲染层（C++）→ 数据流 → Benchmark 场景（GDScript） → GPU 驱动*

### 引擎侧关键文件

| 文件 | 功能 |
|------|------|
| `servers/rendering/renderer_rd/pipeline_warmup_rd.h/.cpp` | 预热调度核心 — 加载/去重/编译/缓存 |
| `servers/rendering/rendering_server.cpp` | ProjectSettings 注册 (`rendering/pipeline_warmup/*`) |
| `main/main.cpp` | 启动时检查 enabled → 触发预热 |
| `servers/rendering/renderer_rd/forward_clustered/` | Forward+ 渲染器预热回调 |
| `servers/rendering/renderer_rd/forward_mobile/` | ForwardMobile 渲染器预热回调 |

### 预热数据流

![Pipeline Warmup 数据流](../godot/benchmark-comparison/no-warmup-vs-warmup/assets/dataflow.png)

*图：完整数据流 — EDITOR-TIME（Manifest 生成）→ RUNTIME 引擎启动（批量编译）→ 场景运行（命中管线）→ ANALYSIS（报告生成）*

---

## 性能对比

### GDExtension vs Native C++

| 指标 | GDExtension (参考) | Native C++ (本工作) | 提升 |
|------|:---:|:---:|:---:|
| 编译吞吐量 | ~19 entries/s | ~11,000 entries/s | **~555×** |
| 1000 条目预热耗时 | ~5.0 s | 0.09 s | **~55×** |
| 覆盖率（无预算截断） | 9.7% (97/1000) | 100% (1000/1000) | **~10×** |
| 集成方式 | Scene Tree + ResourceLoader | 直接 pipeline_create 调用 | 无场景树开销 |

> GDExtension 方案因依赖 Scene Tree 和 ResourceLoader，吞吐量受限于逐帧调度开销。Native C++ 直接调用渲染设备 API，在引擎启动的 0.09s 内即可完成全部 1000 条管线编译。

---

## A/B 对比：无预热 vs 有预热

> **测试配置**：Dense200 场景（800 个独立 StandardMaterial3D 的 MeshInstance3D，0.6s 间隔 Reveal）。  
> GPU: NVIDIA RTX 3060 Laptop / 渲染器: Vulkan Forward+ / 引擎: Godot 4.8.dev  
> **均清除 Shader Cache + Pipeline Cache，冷启动。**

![A/B 对比测试流程](../godot/benchmark-comparison/no-warmup-vs-warmup/assets/ab_test_flow.png)

*图：A/B 对比测试流程 — No Warmup（左侧红色）vs Warmup（右侧绿色）两条对称路径*

![Dense200 场景运行截图](benchmark_results/report/screenshots/scene_midframe.png)

*图 1：Dense200 场景运行中 — 800 个 MeshInstance3D 正逐帧 Reveal*

<video src="benchmark_results/report/screenshots/swam.mp4" controls width="100%"></video>

*图 2：场景运行录屏（mp4 视频，8.87s）*

![No-Warmup vs Warmup 性能对比](benchmark_results/report/charts/no_warmup_vs_warmup_comparison.png)

*图 3：六合一性能分析总图 — Frame Time Overlay、Spike Events、CDF、Log Histogram、KPI Bar、Summary*

### 帧时间 KPI（全帧，30s 窗口）

| 指标 | No Warmup | Warmup | Δ | 变化 |
|------|:---:|:---:|:---:|:---:|
| Mean (ms) | 8.45 | 8.31 | +0.14 | +1.7% |
| p50 (ms) | 6.75 | 6.67 | +0.08 | +1.2% |
| p95 (ms) | 14.68 | 14.73 | −0.05 | −0.3% |
| **p99 (ms)** | **16.67** | 15.32 | **+1.35** | **+8.8%** |
| Max (ms) | 150.0 | 138.2 | +11.8 | +8.5% |

### Spike 事件（帧时间 ≥ 阈值）

| 阈值 | No Warmup | Warmup | Δ |
|------|:---:|:---:|:---:|
| **≥ 16ms** | **29** | 9 | **−20 (−69%)** |
| ≥ 33ms | 2 | 2 | 0 |
| ≥ 50ms | 2 | 2 | 0 |
| ≥ 100ms | 1 | 2 | +1 |

### 启动阶段（前 60 帧）

| 指标 | No Warmup | Warmup | Δ | 变化 |
|------|:---:|:---:|:---:|:---:|
| Mean (ms) | 9.27 | 7.88 | +1.39 | **+17.6%** |
| p95 (ms) | 9.04 | 7.19 | +1.85 | **+25.7%** |
| Max (ms) | 150.0 | 138.2 | +11.8 | +8.5% |

### 结论

- **中等频率卡顿（≥16ms）减少 69%** — 从 29 次降到 9 次，每次卡顿对应 Reveal 触发的首次管线编译
- **启动阶段改善最显著** — 前 60 帧 p95 改善 25.7%，Mean 改善 17.6%
- **稳定帧不受影响** — p95 几乎持平，预热只消除冷启动开销，不改变渲染稳态性能
- **极端 spike（≥100ms）非管线编译导致** — 两种模式下都存在，来自场景初始化和 OS 调度
- **1000 条管线仅需 0.19s** — 以极低启动成本换取显著帧时间稳定性提升

---

## 测试方法

### 测试流程

```
清空 Shader Cache + Pipeline Cache
        │
        ├─ No Warmup ──▶ 空 manifest (0 条目) + --baseline ──▶ 场景运行 → frametimes_no_warmup.csv
        │
        └─ Warmup    ──▶ 1000 条目 manifest + 默认模式 ──▶ 场景运行 → frametimes_warmup.csv
                                                                          │
                                                                   Python 分析脚本
                                                                   ├─ p95 / p99 / Mean
                                                                   ├─ Spike 计数
                                                                   ├─ 前 60 帧统计
                                                                   ├─ matplotlib 六合一图
                                                                   └─ ECharts 交互报告
```

### 测试工具链

| 层级 | 组件 | 语言 | 说明 |
|------|------|------|------|
| 引擎核心 | `PipelineWarmupRD` | C++ | Manifest 加载 → 去重 → 批量编译 → 缓存持久化 |
| 渲染器 | `ForwardClustered / ForwardMobile Provider` | C++ | 注册预热回调 + 运行时增量收集 |
| 场景层 | `BenchmarkController` + `FrameTimeLogger` | GDScript | Reveal 协议 + 逐帧 CSV 记录 |
| 分析 | `analyze_benchmark.py` + ECharts | Python/JS | CSV → KPI → 图表 → HTML 报告 |

### Reveal 协议

800 个 MeshInstance3D 全部隐藏 → 预热完成 → FrameTimeLogger 启动 → 以 **0.6s 间隔**逐步设为可见 → 30s 窗口 → 所有 Reveal 完成后 2s grace → 自动退出。

### 性能影响

预热代码对引擎运行时影响极小：`add_runtime_entry()` 追加 ~1-5μs（Mutex + Vector.push），管线编译本身是毫秒级的。`FrameTimeLogger.gd` 每帧执行一次 delta × 1000 乘法 + Array append，可随时在 autoload 中禁用。

---

## 项目结构

```
GodotShaderWarmup/
├── project.godot                      # 项目配置
├── pipeline_warmup.json               # Manifest (1000 entries)
├── bench/
│   ├── scenes/StressBenchmarkMain_Dense200.tscn  # 800 MeshInstance3D 场景
│   └── scripts/BenchmarkController.gd            # Reveal 协议
├── autoloads/
│   ├── WarmupAutoloads.gd             # GDScript 预热集成 (支持 --baseline / --no-warmup)
│   └── FrameTimeLogger.gd             # 逐帧 CSV 记录
├── addons/shader_warmup_tool/         # 编辑器插件 (Manifest 生成 + 场景合成)
├── gdext/                             # GDExtension (参考实现，本测试中不依赖)
├── benchmark_results/
│   └── report/
│       ├── BENCHMARK_REPORT.md        # 详细基准报告
│       ├── screenshots/               # 截图 + 录屏
│       ├── charts/                    # 六合一性能分析图
│       └── data/                      # CSV 原始数据 + JSON KPI
└── ../godot/
    ├── bin/godot.*.console.exe        # 自编译 Godot (含 PipelineWarmupRD)
    ├── benchmark-final/               # 预热 KPI 报告 (HTML)
    └── benchmark-comparison/          # A/B 对比报告 (HTML)
```

---

## 构建 & 运行

### 构建 Godot 引擎

从 [Godot Engine](https://github.com/godotengine/godot) 源码构建（当前基于 4.8.dev），`PipelineWarmupRD` 已集成到渲染服务器。

```powershell
scons platform=windows target=editor dev_build=yes
# 输出: bin/godot.windows.editor.dev.x86_64.console.exe
```

### 运行基准测试

```powershell
# No Warmup（冷启动，空 manifest）
bin\godot.windows.editor.dev.x86_64.console.exe --path GodotShaderWarmup -- --baseline

# Warmup（冷启动，1000 条目 manifest）
bin\godot.windows.editor.dev.x86_64.console.exe --path GodotShaderWarmup
```

CSV 输出在 `%APPDATA%\Godotpp_userdata\Shader Warm-Up Benchmarkrametimes_*.csv`。

### 分析数据

```powershell
python analyze_comparison.py
# 输出: p95/p99/Spike 统计 + 六合一 matplotlib 图 + comparison_report.json
```

---

## 报告索引

| 报告 | 格式 | 路径 |
|------|------|------|
| 详细基准报告 | Markdown | [BENCHMARK_REPORT.md](benchmark_results/report/BENCHMARK_REPORT.md) |
| A/B 对比报告 | HTML (ECharts) | [no-warmup-vs-warmup.html](../godot/benchmark-comparison/no-warmup-vs-warmup/no-warmup-vs-warmup.html) |
| 预热 KPI 报告 | HTML (ECharts) | [benchmark-final.html](../godot/benchmark-final/benchmark-final.html) |

---

