// No-Warmup vs Warmup Comparison Charts
(function() {
  var style = getComputedStyle(document.documentElement);
  var accent = style.getPropertyValue('--accent').trim();
  var accent2 = style.getPropertyValue('--accent2').trim();
  var ink = style.getPropertyValue('--ink').trim();
  var muted = style.getPropertyValue('--muted').trim();
  var rule = style.getPropertyValue('--rule').trim();
  var bg = style.getPropertyValue('--bg').trim();
  var bg2 = style.getPropertyValue('--bg2').trim();

  // --- Chart 1: Frame Time Overlay ---
  (function() {
    var c = echarts.init(document.getElementById('chart-overlay'), null, { renderer: 'svg' });

    // Load frame time data from CSV embedded data
    var noWarmupData = FRAME_DATA_NO_WARMUP;
    var warmupData = FRAME_DATA_WARMUP;

    var nwSeries = noWarmupData.map(function(d) { return [d[0], d[1]]; });
    var wSeries = warmupData.map(function(d) { return [d[0], d[1]]; });

    c.setOption({
      animation: false,
      color: [accent2, accent],
      title: { text: '', left: 'center' },
      tooltip: { trigger: 'axis', appendToBody: true, valueFormatter: function(v) { return v.toFixed(2) + ' ms'; } },
      legend: { data: ['No Warmup', 'Warmup'], bottom: 0, textStyle: { color: ink } },
      grid: { left: 60, right: 30, top: 20, bottom: 40 },
      xAxis: { type: 'value', name: 'Frame Index', nameTextStyle: { color: muted }, axisLabel: { color: muted }, axisLine: { lineStyle: { color: rule } }, splitLine: { lineStyle: { color: rule } } },
      yAxis: { type: 'value', name: 'Frame Time (ms)', nameTextStyle: { color: muted }, axisLabel: { color: muted }, axisLine: { lineStyle: { color: rule } }, splitLine: { lineStyle: { color: rule } } },
      series: [
        { name: 'No Warmup', type: 'line', data: nwSeries, symbol: 'none', lineStyle: { width: 1.5 }, showSymbol: false },
        { name: 'Warmup', type: 'line', data: wSeries, symbol: 'none', lineStyle: { width: 1.5 }, showSymbol: false }
      ]
    });
    window.addEventListener('resize', function() { c.resize(); });
  })();

  // --- Chart 2: KPI Bar Chart ---
  (function() {
    var c = echarts.init(document.getElementById('chart-kpi'), null, { renderer: 'svg' });
    var noMetrics = [8.45, 14.68, 16.67, 150.0];
    var wMetrics = [8.31, 14.73, 15.32, 138.2];
    var categories = ['Mean', 'p95', 'p99', 'Max'];

    c.setOption({
      animation: false,
      color: [accent2, accent],
      tooltip: { trigger: 'axis', appendToBody: true, valueFormatter: function(v) { return v.toFixed(2) + ' ms'; } },
      legend: { data: ['No Warmup', 'Warmup'], bottom: 0, textStyle: { color: ink } },
      grid: { left: 55, right: 20, top: 20, bottom: 40 },
      xAxis: { type: 'category', data: categories, axisLabel: { color: muted }, axisLine: { lineStyle: { color: rule } } },
      yAxis: { type: 'value', name: 'ms', nameTextStyle: { color: muted }, axisLabel: { color: muted }, axisLine: { lineStyle: { color: rule } }, splitLine: { lineStyle: { color: rule } } },
      series: [
        { name: 'No Warmup', type: 'bar', data: noMetrics.map(function(v, i) { return { value: v, itemStyle: { borderRadius: i === 3 ? [4, 4, 0, 0] : undefined } }; }), barGap: '20%' },
        { name: 'Warmup', type: 'bar', data: wMetrics.map(function(v, i) { return { value: v, itemStyle: { borderRadius: i === 3 ? [4, 4, 0, 0] : undefined } }; }) }
      ]
    });
    window.addEventListener('resize', function() { c.resize(); });
  })();

  // --- Chart 3: Spike Count Comparison ---
  (function() {
    var c = echarts.init(document.getElementById('chart-spikes'), null, { renderer: 'svg' });
    var cats = ['>=16ms', '>=33ms', '>=50ms', '>=100ms'];
    var nwSpikes = [29, 2, 2, 1];
    var wSpikes = [9, 2, 2, 2];

    c.setOption({
      animation: false,
      color: [accent2, accent],
      tooltip: { trigger: 'axis', appendToBody: true },
      legend: { data: ['No Warmup', 'Warmup'], bottom: 0, textStyle: { color: ink } },
      grid: { left: 50, right: 20, top: 20, bottom: 40 },
      xAxis: { type: 'category', data: cats, axisLabel: { color: muted }, axisLine: { lineStyle: { color: rule } } },
      yAxis: { type: 'value', name: 'Count', nameTextStyle: { color: muted }, axisLabel: { color: muted }, axisLine: { lineStyle: { color: rule } }, splitLine: { lineStyle: { color: rule } } },
      series: [
        { name: 'No Warmup', type: 'bar', data: nwSpikes, barGap: '20%' },
        { name: 'Warmup', type: 'bar', data: wSpikes }
      ]
    });
    window.addEventListener('resize', function() { c.resize(); });
  })();

  // --- Chart 4: First 60 Frames Comparison ---
  (function() {
    var c = echarts.init(document.getElementById('chart-first60'), null, { renderer: 'svg' });
    var cats = ['Mean', 'p95', 'Max'];
    var nwVal = [9.27, 9.04, 150.0];
    var wVal = [7.88, 7.19, 138.2];

    c.setOption({
      animation: false,
      color: [accent2, accent],
      tooltip: { trigger: 'axis', appendToBody: true, valueFormatter: function(v) { return v.toFixed(2) + ' ms'; } },
      legend: { data: ['No Warmup', 'Warmup'], bottom: 0, textStyle: { color: ink } },
      grid: { left: 55, right: 20, top: 20, bottom: 40 },
      xAxis: { type: 'category', data: cats, axisLabel: { color: muted }, axisLine: { lineStyle: { color: rule } } },
      yAxis: { type: 'value', name: 'ms', nameTextStyle: { color: muted }, axisLabel: { color: muted }, axisLine: { lineStyle: { color: rule } }, splitLine: { lineStyle: { color: rule } } },
      series: [
        { name: 'No Warmup', type: 'bar', data: nwVal.map(function(v, i) { return { value: v, itemStyle: { borderRadius: i === 2 ? [4, 4, 0, 0] : undefined } }; }), barGap: '20%' },
        { name: 'Warmup', type: 'bar', data: wVal.map(function(v, i) { return { value: v, itemStyle: { borderRadius: i === 2 ? [4, 4, 0, 0] : undefined } }; }) }
      ]
    });
    window.addEventListener('resize', function() { c.resize(); });
  })();
})();
