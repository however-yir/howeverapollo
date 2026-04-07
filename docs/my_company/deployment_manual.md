# Modified by however-yir autonomous driving team

# Deployment Manual

## 1. Machine And Driver Baseline

- Ubuntu 22.04 LTS
- NVIDIA driver >= 535 (GPU machines)
- Docker + NVIDIA Container Toolkit
- Bazel/Node/Python versions follow `modules/my_company/config/dependency_baseline.yaml`

## 2. Dependency Preparation

```bash
# C++ build baseline
bazel --version

# Frontend baseline
node -v
yarn -v

# Python baseline
python3 --version
```

## 3. Select Environment Layer

```bash
# dev / staging / prod
scripts/my_company/apply_env_config.sh dev
```

Generated files:
- `modules/my_company/config/flags/current.flags`
- `modules/dreamview_plus/frontend/packages/dreamview-web/public/runtime-config.js`

## 4. Build

```bash
bazel build //modules/dreamview_plus/...
bazel build //modules/my_company/...
```

## 5. Start Sequence

1. Start Cyber RT base services.
2. Start map/localization prerequisites.
3. Start Dreamview Plus with base + env overlay flags.
4. Start modules according to selected HMI mode.

Example startup command:

```bash
mainboard --flagfile=modules/dreamview_plus/conf/dreamview.conf \
  --flagfile=modules/my_company/config/flags/current.flags
```

## 6. Validation Checklist

- Dreamview branding and links match selected environment.
- Map and storage paths are loaded from `current.flags`.
- Custom unit tests pass.
- Replay/CARLA/performance scripts produce artifacts.
