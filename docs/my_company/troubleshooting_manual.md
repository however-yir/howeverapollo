# Modified by however-yir autonomous driving team

# Troubleshooting Manual

## Common Errors

| Symptom | Likely Cause | Action |
|---|---|---|
| Dreamview still shows old brand | `runtime-config.js` not regenerated | Run `scripts/my_company/apply_env_config.sh <env>` and rebuild frontend |
| Wrong map loaded | `map_dir` not overridden | Check `modules/my_company/config/flags/current.flags` |
| Record/scenario list empty | storage path mismatch | Verify `resource_record_path` / `resource_scenario_path` in env JSON |
| Real-car mode cannot engage | safety check not passed | Confirm `ControlModeSwitch::UpdateSafetyCheckResult(true)` path |
| Perception adapter has no output | vendor adapter not registered | Ensure adapter registration during module init |
| Interface compatibility check fails | proto changed vs baseline | Review changed proto and refresh baseline intentionally |

## Fast Diagnostic Commands

```bash
# Confirm active layered config
cat modules/my_company/config/flags/current.flags

# Re-generate runtime config
scripts/my_company/apply_env_config.sh dev

# Run additive unit tests
bazel test //modules/my_company/...

# Interface compatibility check
python3 modules/my_company/tests/interface_compatibility_check.py
```
