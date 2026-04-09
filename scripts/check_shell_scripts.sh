#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ALLOWLIST_FILE="${ROOT_DIR}/scripts/shellcheck_allowlist.txt"
DENYLIST_FILE="${ROOT_DIR}/scripts/shellcheck_denylist.txt"

if [[ ! -f "${ALLOWLIST_FILE}" ]]; then
  echo "Missing allowlist: ${ALLOWLIST_FILE}"
  exit 1
fi

declare -a ALLOWLIST=()
declare -a DENYLIST=()

while IFS= read -r line; do
  [[ "${line}" =~ ^[[:space:]]*# ]] && continue
  [[ "${line}" =~ ^[[:space:]]*$ ]] && continue
  ALLOWLIST+=("${line}")
done <"${ALLOWLIST_FILE}"

if [[ -f "${DENYLIST_FILE}" ]]; then
  while IFS= read -r line; do
    [[ "${line}" =~ ^[[:space:]]*# ]] && continue
    [[ "${line}" =~ ^[[:space:]]*$ ]] && continue
    DENYLIST+=("${line}")
  done <"${DENYLIST_FILE}"
fi

is_denied() {
  local candidate="$1"
  for denied in "${DENYLIST[@]:-}"; do
    if [[ "${denied}" == "${candidate}" ]]; then
      return 0
    fi
  done
  return 1
}

declare -a TARGETS=()
for relpath in "${ALLOWLIST[@]}"; do
  if is_denied "${relpath}"; then
    continue
  fi

  fullpath="${ROOT_DIR}/${relpath}"
  if [[ ! -f "${fullpath}" ]]; then
    echo "Allowlisted shell script not found: ${relpath}"
    exit 1
  fi
  TARGETS+=("${fullpath}")
done

if [[ "${#TARGETS[@]}" -eq 0 ]]; then
  echo "No shell scripts selected for checking."
  exit 0
fi

if command -v shellcheck >/dev/null 2>&1; then
  shellcheck -S error -x -e SC1090,SC1091 "${TARGETS[@]}"
else
  for script in "${TARGETS[@]}"; do
    bash -n "${script}"
  done
fi

echo "Checked ${#TARGETS[@]} shell scripts."
