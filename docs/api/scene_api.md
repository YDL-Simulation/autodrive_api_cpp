# SceneAPI

`SceneAPI` 是与仿真环境交互的核心类，提供连接、数据获取和车辆控制的完整接口。

```cpp
#include "metacar/metacar.hpp"

metacar::SceneAPI api;
```

## 使用流程

1. 创建 `SceneAPI` 实例
2. 调用 `connect()` 等待仿真器连接
3. 调用 `get_scene_static_data()` 获取静态场景信息
4. 循环调用 `step()` 获取每帧数据
5. 调用 `set_vehicle_control()` 发送控制指令

---

## 方法参考

### connect()

```cpp
void connect();
```

阻塞等待仿真器连接，连接成功后自动加载场景静态数据。

- 在端口 **5061**（JSON 命令通道）和 **5063**（二进制帧流）上等待连接
- 接收仿真器发送的初始化数据（地图配置、路线信息等）
- 连接断开时抛出 `ConnectionClosedError`

```cpp
metacar::SceneAPI api;
api.connect();
// 此时静态数据已加载完成
```

---

### get_scene_static_data()

```cpp
const SceneStaticData &get_scene_static_data() const;
```

返回场景的静态数据，包含路线、道路网络和子场景信息。

- 必须在 `connect()` 之后调用
- 返回 const 引用，数据在整个仿真周期内不变

```cpp
const auto &data = api.get_scene_static_data();

// 访问路线点
for (const auto &point : data.route) {
    std::cout << point.x << ", " << point.y << "\n";
}

// 访问道路信息
for (const auto &road : data.roads) {
    std::cout << "道路 " << road.id << " 有 " << road.lanes.size() << " 条车道\n";
}
```

详见 [SceneStaticData](scene_static.md)。

---

### step()

```cpp
std::optional<SimCarMsg> step();
```

获取下一帧仿真数据。这是主循环的核心方法。

**返回值：**

- `std::optional<SimCarMsg>` — 包含当前帧的所有动态数据
- 返回 `std::nullopt` 表示仿真结束

**行为说明：**

- 首次调用时，会自动向仿真器发送就绪信号
- 每次调用会接收一帧完整的仿真数据（位姿、障碍物、交通灯等）
- 仿真器发送结束信号后，返回 `std::nullopt`，此后 `is_running()` 为 `false`

```cpp
while (auto msg = api.step()) {
    double speed = msg->main_vehicle.speed;
    double x = msg->pose_gnss.pos_x;
    double y = msg->pose_gnss.pos_y;
    // ...
}
// 循环结束，仿真已结束
```

详见 [SimCarMsg](sim_car_msg.md)。

---

### set_vehicle_control()

```cpp
void set_vehicle_control(
    const VehicleControl &vc,
    const std::optional<VLAExtensionOutput> &vla_extension = std::nullopt
);
```

向仿真器发送车辆控制指令。

- 每次 `step()` 之后调用一次
- `vla_extension` 仅在 VLA 场景下需要，普通场景省略即可

```cpp
metacar::VehicleControl ctrl;
ctrl.throttle = 0.5;
ctrl.brake = 0.0;
ctrl.steering = 0.1;
ctrl.gear = metacar::GearMode::DRIVE;

api.set_vehicle_control(ctrl);
```

详见 [VehicleControl](vehicle_control.md)。

---

### retry_level()

```cpp
void retry_level();
```

请求重试当前子场景。调用后，重试标志会在下一次 `set_vehicle_control()` 时发送给仿真器。

```cpp
// 检测到需要重试的情况
api.retry_level();

// 仍需正常发送控制指令，重试标志会附带在其中
metacar::VehicleControl ctrl;
api.set_vehicle_control(ctrl);
```

---

### skip_level()

```cpp
void skip_level();
```

请求跳过当前子场景。调用后，跳过标志会在下一次 `set_vehicle_control()` 时发送给仿真器。

```cpp
// 检测到需要跳过的情况
api.skip_level();

metacar::VehicleControl ctrl;
api.set_vehicle_control(ctrl);
```

---

### is_running()

```cpp
bool is_running() const;
```

检查仿真是否仍在运行。

- `step()` 返回 `std::nullopt` 后变为 `false`
- 连接断开后变为 `false`

```cpp
if (api.is_running()) {
    // 仿真仍在进行
}
```

---

## 异常

### ConnectionClosedError

```cpp
class ConnectionClosedError : public std::runtime_error;
```

当 TCP 连接在通信过程中意外断开时抛出。

```cpp
try {
    api.connect();
    while (auto msg = api.step()) {
        // ...
    }
} catch (const metacar::ConnectionClosedError &e) {
    std::cerr << "连接断开: " << e.what() << "\n";
}
```
