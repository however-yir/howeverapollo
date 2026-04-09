# apollo-scripts

## Introduction
  apollo-scripts contains multiple useful scripts.

## Shellcheck Policy

This repo maintains a controlled shell lint scope through:

- `scripts/shellcheck_allowlist.txt`: scripts that must be linted.
- `scripts/shellcheck_denylist.txt`: scripts temporarily excluded from the allowlist.
- `scripts/check_shell_scripts.sh`: runner that applies allow/deny filters, then executes:
  - `shellcheck` when available
  - `bash -n` fallback when `shellcheck` is unavailable

Run locally:

```bash
bash scripts/check_shell_scripts.sh
```
