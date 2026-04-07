#!/usr/bin/env bash
# Modified by however-yir autonomous driving team.
set -euo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <record_file> [timeout_seconds]"
  exit 1
fi

RECORD_FILE="$1"
TIMEOUT_SECONDS="${2:-300}"

if [[ ! -f "${RECORD_FILE}" ]]; then
  echo "Record file not found: ${RECORD_FILE}"
  exit 2
fi

echo "[scenario-replay] Starting replay for ${RECORD_FILE}"

timeout "${TIMEOUT_SECONDS}" cyber_recorder play -f "${RECORD_FILE}" -l
EXIT_CODE=$?

if [[ ${EXIT_CODE} -ne 0 ]]; then
  echo "[scenario-replay] Replay failed with exit code=${EXIT_CODE}"
  exit ${EXIT_CODE}
fi

echo "[scenario-replay] Replay finished successfully"
