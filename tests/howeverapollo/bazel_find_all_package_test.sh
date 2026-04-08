#!/usr/bin/env bash
set -euo pipefail

ROOT="${TEST_SRCDIR}/${TEST_WORKSPACE}"
tmpdir="$(mktemp -d)"
mkdir -p "${tmpdir}/module_ok" "${tmpdir}/.module_hidden"
touch "${tmpdir}/module_ok/cyberfile.xml"
touch "${tmpdir}/.module_hidden/cyberfile.xml"

python3 - "${ROOT}/scripts/find_all_package.py" "${tmpdir}" <<'PY'
import importlib.util
import sys

module_path = sys.argv[1]
search_root = sys.argv[2]

spec = importlib.util.spec_from_file_location("find_all_package", module_path)
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)

mod.TARGET_PATH = []
mod.search_cyberfile(search_root)

assert f"{search_root}/module_ok" in mod.TARGET_PATH
assert f"{search_root}/.module_hidden" not in mod.TARGET_PATH
PY
