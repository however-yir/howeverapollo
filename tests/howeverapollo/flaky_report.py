#!/usr/bin/env python3
from __future__ import annotations

import os
import re
from pathlib import Path


MARKER_RE = re.compile(r"@pytest\.mark\.flaky")
TEST_DEF_RE = re.compile(r"^def\s+(test_[a-zA-Z0-9_]+)\(")


def main() -> int:
    root = Path(__file__).resolve().parent
    test_files = sorted(root.glob("test_*.py"))

    flaky_tests: list[str] = []
    for path in test_files:
        lines = path.read_text(encoding="utf-8").splitlines()
        for idx, line in enumerate(lines):
            if not MARKER_RE.search(line):
                continue
            if idx + 1 < len(lines):
                match = TEST_DEF_RE.match(lines[idx + 1].strip())
                if match:
                    flaky_tests.append(f"{path.name}::{match.group(1)}")

    print(f"FLAKY_COUNT\t{len(flaky_tests)}")
    for case in flaky_tests:
        print(f"FLAKY\t{case}")

    summary_path = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary_path:
        summary = Path(summary_path)
        content = [
            "## Flaky Test Summary",
            "",
            f"- Flaky markers found: **{len(flaky_tests)}**",
        ]
        if flaky_tests:
            content.append("")
            content.extend([f"- `{case}`" for case in flaky_tests])
        summary.write_text("\n".join(content) + "\n", encoding="utf-8")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
