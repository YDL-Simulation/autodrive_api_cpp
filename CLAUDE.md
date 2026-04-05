# CLAUDE.md

## 项目概述

metacar — 自动驾驶仿真 C++ API 库，为元动力仿真平台提供场景管理与车辆控制接口。

本项目是 Python API (`../autodrive_api_python`) 的 C++ 移植版，去掉了视觉处理部分。面向大学本科生，配合示例仓库 (`../autodrive_examples_cpp`) 使用。学生通过克隆示例仓库开始开发，不应接触本 API 源码。

## 架构

```
include/metacar/
  metacar.hpp      ← 总入口头文件
  geometry.hpp     ← Vector2/Vector3 数学类型
  models.hpp       ← 50+ 数据结构和枚举，含 JSON 序列化
  scene_api.hpp    ← SceneAPI 高级接口（面向用户的核心类）
  sockets.hpp      ← TCP 通信底层（长度前缀二进制协议）
src/
  对应各头文件的实现
```

层次关系：sockets（网络层）→ models（协议层）→ scene_api（业务层）

## 构建

项目提供了 CMakePresets.json，推荐使用 preset 构建（需在 VS Developer Terminal 中执行）：

```bash
# Windows (VS Developer Terminal)
cmake --preset win-debug
cmake --build --preset win-debug

# Linux
cmake --preset linux-debug
cmake --build --preset linux-debug
```

构建产物为静态库。下游通过 `find_package(metacar)` + `target_link_libraries(app PRIVATE metacar::metacar)` 使用。

## 依赖

- C++20
- nlohmann_json 3.12.0（CMake FetchContent 自动拉取）
- Windows: Winsock2 (ws2_32)；POSIX: 标准 socket

无其他外部依赖。

## 代码规范

- 格式化：clang-format，基于 LLVM，列宽 100
- 命名：类/结构体 PascalCase，函数/变量 snake_case，私有成员尾部下划线，枚举值 UPPER_SNAKE_CASE
- 头文件守卫：`#pragma once`
- JSON 字段用 CamelCase（与仿真器协议一致），C++ 成员用 snake_case

## 网络协议

- 端口 5061：JSON 命令通道（ModelSocket）
- 端口 5063：二进制帧流（StreamingSocket）
- 消息格式：4 字节大端长度 + 载荷
- 通信流程：Code1（初始化）→ Code2（就绪）→ Code3/4 循环（帧/控制）→ Code5（结束）

## 注意事项

- 修改 models.hpp 中的结构体时，必须同步更新 models.cpp 中对应的 to_json/from_json
- 公共 API 的变更需考虑对示例仓库 (`autodrive_examples_cpp`) 的影响
- 本库不依赖 OpenCV；`step()` 返回 `StepResult`，其中 `frames` 字段包含 `CameraFrame`（JPEG 原始字节）
- 内部日志统一使用 `detail::log(LogLevel::XXX, msg)`，不要直接用 `std::cout`/`std::cerr`
- 枚举值命名避开 Windows 宏（`ERROR`、`DEBUG` 等），否则会被预处理器展开导致编译失败
