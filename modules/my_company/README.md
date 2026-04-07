# Modified by however-yir autonomous driving team

## Purpose

`modules/my_company` is the additive customization layer for this Apollo fork.

Principles:
- Only add, do not hard-modify upstream core modules where avoidable.
- Keep vendor-dependent logic behind adapters.
- Keep runtime differences in environment configuration (`dev/staging/prod`).

## Layout

- `common/sensor`: Sensor abstraction and registry.
- `perception_adapter`: Adapter entry for integrating self-developed perception.
- `planning_plugin`: Strategy plugin interface and plugin manager.
- `control`: Simulation/real-car mode switch and fault injection gate.
- `config`: Environment layering configs + artifact generator.
- `tests`: Replay/CARLA/perf/interface compatibility test scripts.

## Quick Start

```bash
# 1) Generate environment config artifacts
python3 modules/my_company/config/generate_runtime_artifacts.py --env dev

# 2) (Optional) refresh proto compatibility baseline
python3 modules/my_company/tests/interface_compatibility_check.py --refresh-baseline

# 3) Run additive unit tests
bazel test //modules/my_company/common/sensor:sensor_adapter_registry_test \
  //modules/my_company/perception_adapter:my_perception_adapter_test \
  //modules/my_company/planning_plugin:strategy_plugin_test \
  //modules/my_company/control:control_mode_switch_test
```

## Notes

This layer is designed to be integrated by launch/config wiring without invasive trunk rewrites.
