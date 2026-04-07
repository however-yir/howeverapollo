# Modified by however-yir autonomous driving team

# HWP Apollo (Fork of ApolloAuto/apollo)

本仓库基于 [ApolloAuto/apollo](https://github.com/ApolloAuto/apollo) 进行企业化二次开发，遵循 **“只加不改、优先新增模块”** 原则：

- 主干能力尽量不侵入式修改。
- 自研能力统一落在 `modules/my_company/*`。
- 通过配置注入和适配器接入，降低升级与回归风险。

## 1. 项目用途

本项目用于构建面向量产导向场景的自动驾驶研发平台，覆盖：

- Dreamview 品牌化与信息架构重构。
- 传感器和外部服务解耦（可替换厂商、可多环境部署）。
- 感知/规划/控制插件化扩展。
- 场景回放、CARLA 闭环回归、性能与接口兼容自动化验证。

## 2. 目标车型与业务场景

目标车型（当前假设）：

- 线控底盘中型乘用车平台（支持 steer-by-wire / brake-by-wire / throttle-by-wire）。
- 支持“仿真模式 + 实车模式”双运行形态。

目标业务场景：

- 城市低速园区与限定开放道路。
- 研发联调、回放验证、安全测试（含故障注入）。
- 持续交付与多环境发布（dev/staging/prod）。

## 3. 与 Apollo 上游的关键差异

### 架构与模块

- 新增 `modules/my_company/*` 作为自研承载层。
- 新增传感器抽象层，解耦厂商实现。
- 自研感知通过适配器接入，不直接硬改上游主链路。
- 新增规划策略插件接口与策略管理器。
- 控制模块新增“仿真/实车”模式切换和故障注入开关。

### 配置与部署

- 地图路径、存储路径参数化。
- 外部服务地址改为配置注入。
- 新增 `dev/staging/prod` 分层配置与运行时生成脚本。

### Dreamview 改造

- Dreamview 前端品牌名与 Logo 替换。
- 主题色与导航结构按自定义信息架构重排。
- 前端运行时配置注入（含菜单顺序、外链、品牌配置）。

### 工程质量与测试

- 依赖版本基线文件（Bazel/Node/Python）。
- 前端安全审计流程（含 npm audit 工作流）。
- Bazel 新增 sanitizer 构建配置（ASAN/UBSAN/TSAN）。
- 新增单元测试、场景回放、CARLA 回归、性能基准、接口兼容测试。

### 文档与维护

- 新增拓扑图/数据流图、部署手册、故障排障手册、路线图。
- 设定每月一次 upstream rebase 节奏（脚本 + CI）。

## 4. 目录说明

- `modules/my_company/`：自研功能主目录。
- `modules/my_company/config/environments/`：`dev/staging/prod` 分层配置。
- `scripts/my_company/`：环境配置渲染与启动脚本。
- `docs/my_company/`：拓扑、部署、排障、路线图、维护策略等文档。

## 5. 快速开始（开发环境）

1. 启动 Apollo 开发容器（沿用上游流程）。
2. 选择环境并生成运行时配置：

```bash
./scripts/my_company/apply_env_config.sh dev
```

3. 使用注入配置启动 Dreamview：

```bash
./scripts/my_company/start_dreamview.sh dev
```

4. 运行自研模块测试：

```bash
bazel test //modules/my_company/...
```

## 6. 交付文档入口

- 模块拓扑与数据流图：`docs/my_company/topology_and_dataflow.md`
- 部署手册：`docs/my_company/deployment_manual.md`
- 故障排障手册：`docs/my_company/troubleshooting_manual.md`
- 路线图：`docs/my_company/roadmap.md`
- Upstream Rebase 节奏：`docs/my_company/upstream_rebase_policy.md`

## 7. 许可证

本项目保留并遵循 Apache-2.0 许可证：

- `LICENSE`
- `NOTICE`

上游版权归 Apollo 原始贡献者所有；本仓库仅包含企业化定制与扩展。
