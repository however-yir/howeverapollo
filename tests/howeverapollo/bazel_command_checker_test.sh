#!/usr/bin/env bash
set -euo pipefail

ROOT="${TEST_SRCDIR}/${TEST_WORKSPACE}"
output_file="$(mktemp)"

python3 "${ROOT}/scripts/command_checker.py" \
  --name apollo \
  --command buid \
  --available "build test" \
  >"${output_file}"

grep -q 'Did you mean the following?' "${output_file}"
grep -q 'build' "${output_file}"
