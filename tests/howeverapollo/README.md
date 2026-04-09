# howeverapollo Test Notes

This directory contains lightweight guardrail tests added for CI stability.

## What is covered

- `test_python_shell.py`: Python-level behavior checks for fork-owned scripts.
- `bazel_*_test.sh`: fast Bazel smoke targets for script execution contracts.
- `flaky_report.py`: counts `@pytest.mark.flaky` markers and emits CI summary.

## Local run

```bash
pytest tests/howeverapollo -q
bazel test //tests/howeverapollo:command_checker_fast_test
bazel test //tests/howeverapollo:find_all_package_fast_test
bazel test //tests/howeverapollo:deploy_dry_run_fast_test
python tests/howeverapollo/flaky_report.py
```

## Flaky annotation convention

If a test is temporarily unstable, annotate it explicitly:

```python
@pytest.mark.flaky
```

The report script will surface all marked tests in CI output.
