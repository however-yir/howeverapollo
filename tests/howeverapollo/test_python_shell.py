from __future__ import annotations

import importlib.util
import subprocess
from pathlib import Path


TEST_DIR = Path(__file__).resolve().parent
REPO_ROOT = TEST_DIR.parent.parent
FORK_ROOT = REPO_ROOT / "howeverapollo"


def _load_module(module_name: str, file_path: Path):
    spec = importlib.util.spec_from_file_location(module_name, file_path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"Failed to load module: {file_path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def _candidate_script_dirs() -> list[Path]:
    dirs = [REPO_ROOT / "scripts", FORK_ROOT / "scripts"]
    return [d for d in dirs if d.exists()]


def test_command_checker_suggests_close_match_in_script_dirs() -> None:
    script_dirs = _candidate_script_dirs()
    assert script_dirs, "No scripts directory found for testing"

    for index, scripts_dir in enumerate(script_dirs):
        module = _load_module(f"command_checker_{index}", scripts_dir / "command_checker.py")
        checker = module.CommandChecker("buid", ["build", "test"], "apollo")
        checker.spelling_suggestions()
        assert "build" in checker.alternative_commands


def test_find_all_package_discovers_cyberfile_and_skips_hidden_dirs(tmp_path: Path) -> None:
    module = _load_module("find_all_package", REPO_ROOT / "scripts" / "find_all_package.py")

    visible_pkg = tmp_path / "module_visible"
    visible_pkg.mkdir(parents=True)
    (visible_pkg / "cyberfile.xml").write_text("<xml />", encoding="utf-8")

    hidden_pkg = tmp_path / ".hidden_module"
    hidden_pkg.mkdir(parents=True)
    (hidden_pkg / "cyberfile.xml").write_text("<xml />", encoding="utf-8")

    module.TARGET_PATH = []
    module.search_cyberfile(str(tmp_path))

    assert str(visible_pkg) in module.TARGET_PATH
    assert str(hidden_pkg) not in module.TARGET_PATH


def test_deploy_local_sanity_check_dry_run_executes_successfully() -> None:
    script_path = REPO_ROOT / "scripts" / "deploy_local_sanity_check.sh"

    result = subprocess.run(
        ["bash", str(script_path), "--dry-run"],
        cwd=REPO_ROOT,
        text=True,
        capture_output=True,
        check=False,
    )

    assert result.returncode == 0, result.stderr
    combined_output = f"{result.stdout}\n{result.stderr}"
    assert "Dry run mode enabled" in combined_output
    assert "Dry run finished." in combined_output


def test_deploy_local_sanity_check_help_outputs_usage() -> None:
    script_path = REPO_ROOT / "scripts" / "deploy_local_sanity_check.sh"

    result = subprocess.run(
        ["bash", str(script_path), "--help"],
        cwd=REPO_ROOT,
        text=True,
        capture_output=True,
        check=False,
    )

    assert result.returncode == 0
    assert "Usage:" in result.stdout


def test_deploy_local_sanity_check_unknown_argument_fails_fast() -> None:
    script_path = REPO_ROOT / "scripts" / "deploy_local_sanity_check.sh"

    result = subprocess.run(
        ["bash", str(script_path), "--unknown-flag"],
        cwd=REPO_ROOT,
        text=True,
        capture_output=True,
        check=False,
    )

    assert result.returncode == 2
    combined_output = f"{result.stdout}\n{result.stderr}"
    assert "Unknown argument" in combined_output
