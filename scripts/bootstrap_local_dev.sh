#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
RUN=0

if [[ "${1:-}" == "--run" ]]; then
  RUN=1
fi

require_cmd() {
  local cmd="$1"
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "Missing required command: $cmd" >&2
    exit 1
  fi
}

if [[ "$(uname -s)" != "Linux" ]]; then
  echo "howeverapollo local build is designed for Linux hosts." >&2
  exit 1
fi

require_cmd bash
require_cmd git
require_cmd python3

if ! command -v bazel >/dev/null 2>&1 && ! command -v bazelisk >/dev/null 2>&1; then
  echo "Please install bazel or bazelisk before bootstrap." >&2
  exit 1
fi

if ! command -v docker >/dev/null 2>&1; then
  echo "Docker is recommended for first build isolation (optional but strongly suggested)." >&2
fi

cat <<'STEPS'
Bootstrap steps:
  1) bash apollo.sh config
  2) bash apollo.sh build_cpu cyber
  3) bazel test //tests/howeverapollo:command_checker_fast_test
STEPS

if [[ "${RUN}" -eq 1 ]]; then
  cd "${ROOT_DIR}"
  bash apollo.sh config
  bash apollo.sh build_cpu cyber
  bazel test //tests/howeverapollo:command_checker_fast_test
fi
