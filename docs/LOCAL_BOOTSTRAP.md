# Local Bootstrap (Bazel)

## 1) Environment baseline

- Linux host (Ubuntu 20.04/22.04 recommended)
- Python 3.8+
- Bazel or Bazelisk
- Docker (recommended for first setup)

## 2) Guided bootstrap

```bash
./scripts/bootstrap_local_dev.sh
```

## 3) Execute bootstrap directly

```bash
./scripts/bootstrap_local_dev.sh --run
```

This performs:

1. `bash apollo.sh config`
2. `bash apollo.sh build_cpu cyber`
3. `bazel test //tests/howeverapollo:command_checker_fast_test`

## 4) Optional quick sanity checks

```bash
pytest tests/howeverapollo -q
bash scripts/deploy_local_sanity_check.sh --dry-run
```
