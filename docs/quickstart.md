# 快速入门

本指南将帮助你从零开始与仿真环境建立连接并控制车辆。

!!! tip "还没搭建环境？"
    请先按照 [环境搭建](getting-started.md) 克隆示例仓库并完成构建。

## 基本用法

使用 MetaCar 的基本步骤如下：

### 1. 引入头文件

```cpp
#include "metacar/metacar.hpp"
```

这个头文件会包含所有公共 API，包括 `SceneAPI`、`VehicleControl`、`Vector2` 等。

### 2. 创建 SceneAPI 实例并连接

```cpp
metacar::SceneAPI api;
api.connect();  // 阻塞直到仿真器连接
```

`connect()` 会在端口 5061 和 5063 上等待仿真器主动连接。连接成功后，会自动加载场景的静态数据（地图、路线等）。

### 3. 获取场景静态数据

```cpp
const auto &static_data = api.get_scene_static_data();
// 静态数据包含路线点、道路信息、子场景信息等
```

### 4. 进入主循环

```cpp
while (auto msg = api.step()) {
    // msg 是 std::optional<SimCarMsg>
    // 包含车辆状态、传感器数据、障碍物信息等

    // 创建控制命令
    metacar::VehicleControl ctrl;
    ctrl.throttle = 0.5;   // 油门 (0.0 ~ 1.0)
    ctrl.steering = 0.0;   // 方向盘 (-1.0 左 ~ 1.0 右)
    ctrl.gear = metacar::GearMode::DRIVE;

    // 发送控制命令
    api.set_vehicle_control(ctrl);
}
```

`step()` 返回 `std::nullopt` 时表示仿真结束，循环自动退出。

## 完整示例

以下是一个完整的示例程序，让车辆以低速直线前进并打印位置信息：

```cpp
#include "metacar/metacar.hpp"
#include <iomanip>
#include <iostream>

int main() {
    metacar::SceneAPI api;

    std::cout << "等待仿真器连接...\n";
    api.connect();
    std::cout << "已连接!\n";

    // 获取静态数据
    const auto &static_data = api.get_scene_static_data();
    std::cout << "路线点数量: " << static_data.route.size() << "\n";

    // 主循环
    while (auto msg = api.step()) {
        // 读取车辆位姿
        const auto &pose = msg->pose_gnss;
        double speed = msg->main_vehicle.speed;

        std::cout << std::fixed << std::setprecision(2)
                  << "位置=(" << pose.pos_x << ", " << pose.pos_y << ")  "
                  << "速度=" << speed << " m/s\n";

        // 发送控制指令
        metacar::VehicleControl ctrl;
        ctrl.gear = metacar::GearMode::DRIVE;
        ctrl.throttle = 0.1;  // 10% 油门
        api.set_vehicle_control(ctrl);
    }

    std::cout << "仿真结束。\n";
    return 0;
}
```

## 通信流程

程序与仿真器之间的通信按以下顺序进行：

```
你的程序                        仿真器
   |                              |
   |  connect() — 等待连接         |
   |<---- TCP 连接 (5061/5063) ---|
   |<---- 初始化数据 (地图信息) ----|
   |                              |
   |  step() — 首次调用            |
   |---- 就绪信号 ----------------->|
   |<---- 帧数据 (车辆/障碍物等) ---|
   |                              |
   |  set_vehicle_control()        |
   |---- 控制指令 ----------------->|
   |                              |
   |  step() / set_vehicle_control() 循环...
   |                              |
   |<---- 结束信号 ----------------|
   |  step() 返回 std::nullopt     |
```

## VLA 场景（可选）

如遇到 VLA（Vision-Language-Action）特殊场景，需要在控制指令中附加额外的感知结果。详见 [VLA 场景](advanced/vla.md)。

## 下一步

- 查看 [SceneAPI 参考](api/scene_api.md) 了解所有可用方法
- 查看 [车辆控制](api/vehicle_control.md) 了解控制参数的详细说明
- 查看 [仿真动态数据](api/sim_car_msg.md) 了解每帧可获取的所有数据
