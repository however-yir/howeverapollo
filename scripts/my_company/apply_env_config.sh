#!/usr/bin/env bash
# Modified by however-yir autonomous driving team.
set -euo pipefail

ENVIRONMENT="${1:-dev}"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

python3 "${ROOT_DIR}/modules/my_company/config/generate_runtime_artifacts.py" \
  --env "${ENVIRONMENT}" \
  --config-root "${ROOT_DIR}/modules/my_company/config/environments" \
  --flagfile-output "${ROOT_DIR}/modules/my_company/config/flags/current.flags" \
  --runtime-js-output "${ROOT_DIR}/modules/dreamview_plus/frontend/packages/dreamview-web/public/runtime-config.js"

echo "[my_company] Generated env artifacts for ${ENVIRONMENT}" \
  "at modules/my_company/config/flags/current.flags and dreamview runtime-config.js"
