#!/usr/bin/env python3
"""Modified by however-yir autonomous driving team.
Generate environment-layered Dreamview gflags and frontend runtime config.
"""

import argparse
import json
from pathlib import Path


RUNTIME_TO_FLAG = {
    "server_ports": "server_ports",
    "map_dir": "map_dir",
    "maps_data_path": "maps_data_path",
    "resource_record_path": "resource_record_path",
    "resource_rtk_record_path": "resource_rtk_record_path",
    "resource_scenario_path": "resource_scenario_path",
    "resource_dynamic_model_path": "resource_dynamic_model_path",
    "dynamic_model_root_path": "dynamic_model_root_path",
    "dynamic_model_library_path": "dynamic_model_library_path",
    "default_rtk_record_path": "default_rtk_record_path",
    "default_rtk_record_file": "default_rtk_record_file",
}


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate Dreamview runtime artifacts from env JSON config."
    )
    parser.add_argument("--env", required=True, choices=["dev", "staging", "prod"])
    parser.add_argument(
        "--config-root",
        default="modules/my_company/config/environments",
        help="Directory containing env JSON files.",
    )
    parser.add_argument(
        "--flagfile-output",
        default="modules/my_company/config/flags/current.flags",
        help="Output gflags file path.",
    )
    parser.add_argument(
        "--runtime-js-output",
        default="modules/dreamview_plus/frontend/packages/dreamview-web/public/runtime-config.js",
        help="Output runtime-config.js path.",
    )
    return parser.parse_args()


def write_flagfile(runtime_cfg: dict, output_path: Path, env_name: str) -> None:
    lines = [
        "# Modified by however-yir autonomous driving team.",
        f"# Generated environment: {env_name}",
    ]
    for runtime_key, flag_key in RUNTIME_TO_FLAG.items():
        value = runtime_cfg.get(runtime_key)
        if value is None:
            continue
        lines.append(f"--{flag_key}={value}")

    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def write_runtime_js(env_cfg: dict, output_path: Path) -> None:
    runtime_payload = {
        "meta": env_cfg.get("meta", {}),
        "dreamview": env_cfg.get("dreamview", {}),
        "external_services": env_cfg.get("external_services", {}),
    }

    js = (
        "/* Modified by however-yir autonomous driving team. */\n"
        "window.__MY_COMPANY_CONFIG__ = "
        + json.dumps(runtime_payload, ensure_ascii=False, indent=2)
        + ";\n"
        "if (window.__MY_COMPANY_CONFIG__?.dreamview?.brand_name) {\n"
        "  document.title = window.__MY_COMPANY_CONFIG__.dreamview.brand_name;\n"
        "}\n"
    )

    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(js, encoding="utf-8")


def main() -> None:
    args = parse_args()
    config_path = Path(args.config_root) / f"{args.env}.json"

    if not config_path.exists():
        raise FileNotFoundError(f"Missing environment config: {config_path}")

    env_cfg = json.loads(config_path.read_text(encoding="utf-8"))
    write_flagfile(env_cfg.get("runtime", {}), Path(args.flagfile_output), args.env)
    write_runtime_js(env_cfg, Path(args.runtime_js_output))
    print(f"Generated artifacts for env={args.env}")


if __name__ == "__main__":
    main()
