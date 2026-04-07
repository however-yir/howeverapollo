#!/usr/bin/env python3
"""Modified by however-yir autonomous driving team.
Detects breaking changes in proto interfaces by hash comparison.
"""

import argparse
import hashlib
import json
from pathlib import Path


DEFAULT_PROTO_ROOT = Path("modules/common_msgs")
DEFAULT_BASELINE = Path("modules/my_company/tests/proto_baseline_sha256.json")


def sha256_text(content: str) -> str:
    return hashlib.sha256(content.encode("utf-8")).hexdigest()


def collect_proto_hashes(proto_root: Path) -> dict:
    hashes = {}
    for proto_file in sorted(proto_root.rglob("*.proto")):
        hashes[str(proto_file)] = sha256_text(proto_file.read_text(encoding="utf-8"))
    return hashes


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Check proto compatibility drift.")
    parser.add_argument("--proto-root", default=str(DEFAULT_PROTO_ROOT))
    parser.add_argument("--baseline", default=str(DEFAULT_BASELINE))
    parser.add_argument(
        "--refresh-baseline",
        action="store_true",
        help="Overwrite baseline hashes with current snapshot.",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    proto_root = Path(args.proto_root)
    baseline_path = Path(args.baseline)

    current = collect_proto_hashes(proto_root)

    if args.refresh_baseline:
        baseline_path.parent.mkdir(parents=True, exist_ok=True)
        baseline_path.write_text(json.dumps(current, indent=2), encoding="utf-8")
        print(f"Baseline refreshed: {baseline_path}")
        return

    if not baseline_path.exists():
        raise FileNotFoundError(
            f"Baseline missing: {baseline_path}. Run with --refresh-baseline first."
        )

    baseline = json.loads(baseline_path.read_text(encoding="utf-8"))

    removed = sorted(set(baseline.keys()) - set(current.keys()))
    changed = sorted(
        key for key in (set(baseline.keys()) & set(current.keys())) if baseline[key] != current[key]
    )

    if not removed and not changed:
        print("Interface compatibility check passed.")
        return

    print("Interface compatibility check failed.")
    if removed:
        print("Removed proto files:")
        for path in removed:
            print(f"  - {path}")
    if changed:
        print("Changed proto files:")
        for path in changed:
            print(f"  - {path}")
    raise SystemExit(1)


if __name__ == "__main__":
    main()
