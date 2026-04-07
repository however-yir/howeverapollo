#!/usr/bin/env bash
# Modified by however-yir autonomous driving team.
set -euo pipefail

DURATION_SEC="${1:-60}"
OUT_DIR="${2:-/tmp/my_company_perf}"
mkdir -p "${OUT_DIR}"

echo "[perf] collecting CPU/GPU/latency for ${DURATION_SEC}s"

date > "${OUT_DIR}/meta.txt"
echo "duration_sec=${DURATION_SEC}" >> "${OUT_DIR}/meta.txt"

# CPU snapshot
(top -l 1 | head -n 20) > "${OUT_DIR}/cpu.txt" || true

# GPU snapshot (if available)
if command -v nvidia-smi >/dev/null 2>&1; then
  nvidia-smi --query-gpu=timestamp,name,utilization.gpu,memory.used,memory.total --format=csv > "${OUT_DIR}/gpu.csv"
else
  echo "nvidia-smi unavailable" > "${OUT_DIR}/gpu.csv"
fi

# Latency placeholder - wire to /apollo/common/latency_records in production.
echo "p50_ms=0" > "${OUT_DIR}/latency.txt"
echo "p95_ms=0" >> "${OUT_DIR}/latency.txt"
echo "p99_ms=0" >> "${OUT_DIR}/latency.txt"

echo "[perf] benchmark artifacts written to ${OUT_DIR}"
