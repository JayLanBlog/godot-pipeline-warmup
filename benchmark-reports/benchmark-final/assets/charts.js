(function() {
  var s = getComputedStyle(document.documentElement);
  var accent = s.getPropertyValue('--accent').trim();
  var accent2 = s.getPropertyValue('--accent2').trim();
  var ink = s.getPropertyValue('--ink').trim();
  var muted = s.getPropertyValue('--muted').trim();
  var rule = s.getPropertyValue('--rule').trim();
  var bg2 = s.getPropertyValue('--bg2').trim();
  var red = '#f85149';

  // KPI bar
  var kpi = echarts.init(document.getElementById('chart-kpi'), null, { renderer: 'svg' });
  kpi.setOption({
    animation: false, color: [accent, accent2],
    tooltip: { appendToBody: true },
    legend: { textStyle: { color: ink } },
    grid: { left: 50, right: 20, top: 30, bottom: 40 },
    xAxis: { type: 'category', data: ['p95 ms','p99 ms','Spikes>=33ms','Mean ms'],
      axisLabel: { color: ink, rotate: 0 }, axisLine: { lineStyle: { color: rule } } },
    yAxis: { type: 'value', axisLabel: { color: muted }, splitLine: { lineStyle: { color: rule } } },
    series: [
      { name: 'Baseline', type: 'bar', barGap: '10%', data: [14.73, 15.32, 2, 8.31],
        label: { show: true, position: 'top', color: ink, fontSize: 11 } },
      { name: 'Warmup', type: 'bar', data: [14.73, 15.32, 2, 8.31],
        label: { show: true, position: 'top', color: ink, fontSize: 11 } }
    ]
  });
  window.addEventListener('resize', function() { kpi.resize(); });

  // Throughput bar
  var tp = echarts.init(document.getElementById('chart-throughput'), null, { renderer: 'svg' });
  tp.setOption({
    animation: false, color: [accent, accent2],
    tooltip: { appendToBody: true },
    legend: { textStyle: { color: ink } },
    grid: { left: 50, right: 20, top: 30, bottom: 40 },
    xAxis: { type: 'category', data: ['Compiled','Time(s)','Entries/s'],
      axisLabel: { color: ink }, axisLine: { lineStyle: { color: rule } } },
    yAxis: { type: 'value', axisLabel: { color: muted }, splitLine: { lineStyle: { color: rule } } },
    series: [
      { name: 'Native C++ (This Work)', type: 'bar', data: [1000, 0.09, 11111],
        label: { show: true, position: 'top', color: ink, fontSize: 11 } },
      { name: 'GDExtension (Ref)', type: 'bar', data: [97, 5.0, 19.4],
        label: { show: true, position: 'top', color: ink, fontSize: 11 } }
    ]
  });
  window.addEventListener('resize', function() { tp.resize(); });

  // Ref comparison
  var ref = echarts.init(document.getElementById('chart-ref'), null, { renderer: 'svg' });
  ref.setOption({
    animation: false, color: [accent, accent2],
    tooltip: { appendToBody: true },
    legend: { textStyle: { color: ink } },
    grid: { left: 50, right: 20, top: 30, bottom: 40 },
    xAxis: { type: 'category', data: ['p95 (ms)','p99 (ms)','Spikes>=33ms'],
      axisLabel: { color: ink }, axisLine: { lineStyle: { color: rule } } },
    yAxis: { type: 'value', axisLabel: { color: muted }, splitLine: { lineStyle: { color: rule } } },
    series: [
      { name: 'This Work (RTX 3060)', type: 'bar', data: [14.73, 15.32, 2],
        label: { show: true, position: 'top', color: ink, fontSize: 11 } },
      { name: 'Reference (RTX 4050)', type: 'bar', data: [7.15, 8.33, 1],
        label: { show: true, position: 'top', color: ink, fontSize: 11 } }
    ]
  });
  window.addEventListener('resize', function() { ref.resize(); });
})();
