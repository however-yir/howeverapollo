# howeverapollo - Apollo 自动驾驶工程化平台 | Apollo-based Autonomous Driving Platform

[![Docs](https://img.shields.io/badge/docs-README-0A7EFA)](https://github.com/however-yir/howeverapollo#readme)
[![Smoke](https://github.com/however-yir/howeverapollo/actions/workflows/apollo-smoke.yml/badge.svg)](https://github.com/however-yir/howeverapollo/actions/workflows/apollo-smoke.yml)
[![License](https://img.shields.io/badge/license-Apache--2.0-16A34A)](./LICENSE)
[![Status](https://img.shields.io/badge/status-active-2563EB)](https://github.com/however-yir/howeverapollo)
[![Type](https://img.shields.io/badge/type-fork--customized-F59E0B)](https://github.com/however-yir/howeverapollo)

> Status: `active`
>
> Upstream: `ApolloAuto/apollo`
>
> 非官方声明（Non-Affiliation）:
> 本仓库为社区维护的衍生项目，与上游项目所属组织或其关联公司无隶属、无官方背书关系。
>
> 商标声明（Trademark Notice）:
> 上游项目名称、Logo 与相关商标归其各自权利人所有；本仓库仅用于兼容性与来源说明，不主张其商标权。
>
> Series: [howevercarla](https://github.com/however-yir/howevercarla) · [howeverautoware](https://github.com/however-yir/howeverautoware) · [howeverpilot](https://github.com/however-yir/howeverpilot)

🔥 面向自动驾驶全栈研发的 Apollo 二次开发主仓，重点落在规划控制、Dreamview 定制与回归验证。  
🚀 强调“可运行 + 可维护 + 可解释”的工程主线，而不是一次性 demo 式改名 fork。  
⭐ 适合作为自动驾驶作品线中的中枢仓库，与 `howevercarla`、`howeverautoware`、`howeverpilot` 配合阅读。

## 项目快照

- 定位：自动驾驶主栈中的规划控制与平台工程仓库。
- 亮点：Dreamview 定制、插件化演进空间、CARLA 回归入口、文档化协作流程。
- 最短运行路径：`bazel build //...`
- 合规入口：上游归属、许可证和后续差异请优先查看仓库前部说明与 `docs/`。

## 自动驾驶作品线分工

| Repo | 主要角色 | 最适合看什么 |
| --- | --- | --- |
| `howevercarla` | 仿真与验证底座 | UE5、场景、可复现实验、验证环境 |
| `howeverautoware` | ROS 2 车辆栈集成 | 感知/规划/控制集成与回归流程 |
| `howeverapollo` | 主栈平台工程 | Dreamview、规划控制、平台化改造 |
| `howeverpilot` | 端侧驾驶软件 | 运行时配置、健康检查、车辆接入 |

## 目录

- [1. 项目概述](#1-项目概述)
- [2. 目标与使用场景](#2-目标与使用场景)
- [3. 功能与能力边界](#3-功能与能力边界)
- [4. 技术栈与依赖](#4-技术栈与依赖)
- [5. 仓库结构说明](#5-仓库结构说明)
- [6. 快速开始](#6-快速开始)
- [7. 配置与环境建议](#7-配置与环境建议)
- [8. 开发与测试流程](#8-开发与测试流程)
- [9. 发布与协作规范](#9-发布与协作规范)
- [10. 路线图建议](#10-路线图建议)
- [11. 贡献指南](#11-贡献指南)
- [12. License](#12-license)

## 1. 项目概述

本仓库面向真实工程场景构建，重点强调以下原则：

- 文档可读：便于团队快速理解上下文与边界。
- 结构清晰：模块职责明确，便于多人协作。
- 演进友好：支持持续迭代与版本化管理。

## 2. 目标与使用场景

本仓库适用于以下场景：

- 作为业务功能开发与验证的工程基座。
- 作为团队内部的能力沉淀与知识共享仓库。
- 作为二次开发与集成扩展的起点。

## 3. 功能与能力边界

当前重点能力包括：
- 覆盖自动驾驶关键链路与工程化组件。
- 支持配置分层、模块扩展与回归验证。
- 适配研发、仿真、联调与交付场景。

当前边界说明：

- 优先保证主流程稳定与可维护。
- 复杂能力按模块扩展，不在单次迭代中堆叠过多变更。
- 所有新增功能建议配套文档与测试。

## 4. 技术栈与依赖

当前仓库可识别的技术栈如下：
- Node.js / JavaScript
- Python
- C/C++ / CMake
- Bazel

依赖管理建议：

- 锁定关键依赖版本，避免隐性升级带来的回归风险。
- 在 CI 中增加基础构建与测试校验。
- 新增第三方依赖时，补充用途说明与安全评估。

## 5. 仓库结构说明

建议优先阅读以下路径：

- \：项目整体说明与入口。
- \ 或同类目录：架构、规范、部署、FAQ 等。
- 业务源码目录：按仓库实际模块组织查看。

如需长期维护，建议保持以下约束：

- 公共能力下沉为共享模块。
- 场景能力通过独立目录隔离。
- 配置、脚本、文档三者保持一致更新。

## 6. 快速开始

1. 克隆仓库：

```bash
git clone https://github.com/however-yir/howeverapollo.git
cd howeverapollo
```

2. 首次构建建议先走 bootstrap（降低 Bazel 首次门槛）：

```bash
./scripts/bootstrap_local_dev.sh
# 真正执行初始化 + 最小构建 + 最小测试
# ./scripts/bootstrap_local_dev.sh --run
```

3. 常规构建：

```bash
bazel build //...
```

4. 首次运行建议先执行最小验证：

- 能否完成依赖安装。
- 能否成功启动核心流程。
- 能否通过基础测试或静态检查。

完整说明见：`docs/LOCAL_BOOTSTRAP.md`

## 7. 配置与环境建议

建议将环境配置分为三层：

- 本地开发（dev）
- 集成联调（staging）
- 生产发布（prod）

推荐做法：

- 使用 \ 或样例配置文件管理参数模板。
- 将密钥、令牌、账号等敏感信息放入环境变量或密钥管理系统。
- 对数据库、缓存、外部 API 地址使用可切换配置。

## 8. 开发与测试流程

推荐工作流：

1. 基于默认分支创建功能分支。
2. 小步提交，确保每次提交目标明确。
3. 本地完成构建与测试后再推送。
4. 通过 Pull Request 完成评审与合并。

测试建议：

- 单元测试覆盖核心业务逻辑。
- 集成测试覆盖关键接口与主流程。
- 对高风险改动补充回归用例。

推荐最小本地检查命令：

```bash
pytest tests/howeverapollo -q
bazel test //tests/howeverapollo:command_checker_fast_test //tests/howeverapollo:find_all_package_fast_test //tests/howeverapollo:deploy_dry_run_fast_test
bash scripts/deploy_local_sanity_check.sh --dry-run
```

## 9. 发布与协作规范

发布建议：

- 使用语义化版本（如 \）。
- 在发布说明中明确新增、修复与不兼容变更。
- 关键发布前执行一次完整回归。

协作建议：

- 需求、设计、代码、测试保持同频更新。
- 重大改动先在文档中定义边界再实施。
- 统一 issue / PR 模板，降低沟通成本。

## 10. 路线图建议

可按以下顺序推进：

1. 稳定主流程，补齐最小可观测性。
2. 优化模块边界，降低耦合度。
3. 提升自动化测试覆盖率。
4. 完善部署与运维手册。
5. 逐步引入性能优化与安全加固。

## 11. 贡献指南

欢迎以 Issue / PR 方式参与改进，建议提交时包含：

- 变更背景与目标
- 关键实现说明
- 测试结果或验证步骤
- 兼容性与风险评估

## 12. License

本仓库遵循当前项目中已有的 License 文件约定。