# MetaCar C++ API

MetaCar 是一个自动驾驶仿真 C++ API 库，为 YDL 仿真平台提供场景管理与车辆控制接口。

本库面向大学本科生，配合示例仓库使用。通过简洁的 API，你可以快速连接仿真环境、获取传感器数据并控制车辆。

## 核心特性

- **简洁的接口** — 核心类 `SceneAPI` 仅需 5 个方法即可完成完整的仿真交互
- **丰富的数据模型** — 涵盖道路、车辆、障碍物、交通灯等 50+ 数据结构
- **跨平台支持** — 同时支持 Windows 和 Linux
- **零外部依赖** — 唯一依赖 nlohmann_json，由 CMake 自动拉取
- **C++20** — 使用现代 C++ 特性

## 快速一览

```cpp
#include "metacar/metacar.hpp"

int main() {
    metacar::SceneAPI api;
    api.connect();  // 等待仿真器连接

    while (auto msg = api.step()) {  // 获取每帧数据
        // 读取车辆状态
        double speed = msg->main_vehicle.speed;

        // 发送控制指令
        metacar::VehicleControl ctrl;
        ctrl.throttle = 0.3;
        ctrl.gear = metacar::GearMode::DRIVE;
        api.set_vehicle_control(ctrl);
    }
}
```

## 文档导航

<div class="grid cards" markdown>

-   :material-rocket-launch:{ .lg .middle } **环境搭建**

    ---

    安装依赖、构建库、集成到项目

    [:octicons-arrow-right-24: 开始搭建](getting-started.md)

-   :material-play-circle:{ .lg .middle } **快速入门**

    ---

    从零开始编写第一个仿真程序

    [:octicons-arrow-right-24: 查看教程](quickstart.md)

-   :material-book-open-variant:{ .lg .middle } **API 参考**

    ---

    完整的类、结构体、枚举参考

    [:octicons-arrow-right-24: 浏览 API](api/scene_api.md)

-   :material-star-four-points:{ .lg .middle } **VLA 场景**

    ---

    Vision-Language-Action 进阶场景

    [:octicons-arrow-right-24: 了解更多](advanced/vla.md)

</div>
