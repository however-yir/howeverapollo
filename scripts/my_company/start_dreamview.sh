#!/usr/bin/env bash
# Modified by however-yir autonomous driving team.
set -euo pipefail

ENVIRONMENT="${1:-dev}"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

"${ROOT_DIR}/scripts/my_company/apply_env_config.sh" "${ENVIRONMENT}"

BASE_CONF="${ROOT_DIR}/modules/dreamview_plus/conf/dreamview.conf"
EXTRA_FLAGS="${ROOT_DIR}/modules/my_company/config/flags/current.flags"

echo "[my_company] base config: ${BASE_CONF}"
echo "[my_company] extra flags: ${EXTRA_FLAGS}"
echo "[my_company] start command (example):"
echo "  mainboard --flagfile=${BASE_CONF} --flagfile=${EXTRA_FLAGS}"
