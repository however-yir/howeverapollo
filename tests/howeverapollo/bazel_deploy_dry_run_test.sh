#!/usr/bin/env bash
set -euo pipefail

ROOT="${TEST_SRCDIR}/${TEST_WORKSPACE}"
output_file="$(mktemp)"

bash "${ROOT}/scripts/deploy_local_sanity_check.sh" --dry-run >"${output_file}" 2>&1

grep -q 'Dry run mode enabled' "${output_file}"
grep -q 'Dry run finished.' "${output_file}"
