#!/usr/bin/env bash
# Modified by however-yir autonomous driving team.
set -euo pipefail

CARLA_HOST="${CARLA_HOST:-127.0.0.1}"
CARLA_PORT="${CARLA_PORT:-2000}"
SCENARIO_SUITE="${1:-Town05-RouteSetA}"
RESULT_DIR="${2:-/tmp/my_company_carla_results}"

mkdir -p "${RESULT_DIR}"

echo "[carla-regression] host=${CARLA_HOST} port=${CARLA_PORT} suite=${SCENARIO_SUITE}"
echo "[carla-regression] result_dir=${RESULT_DIR}"

# Replace with your bridge and evaluator command in production usage.
echo "[carla-regression] Launch bridge and evaluator here"

echo "suite=${SCENARIO_SUITE}" > "${RESULT_DIR}/summary.txt"
echo "status=placeholder_success" >> "${RESULT_DIR}/summary.txt"
