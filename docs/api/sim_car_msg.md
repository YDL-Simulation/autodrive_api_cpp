# 仿真动态数据

每次调用 `SceneAPI::step()` 返回 `StepResult`，其中包含当前帧的动态信息 (`SimCarMsg`) 和摄像头图像 (`CameraFrame`)。

## 单位说明

除特别说明外，文档中涉及的物理量默认使用以下单位：

| 物理量 | 单位 |
|--------|------|
| 长度 / 位置 | 米 (m) |
| 时间 | 秒 (s) |
| 速度 | 米每秒 (m/s) |
| 角度 | 弧度 (rad) |

---

## SimCarMsg

仿真每帧返回的核心数据结构。

```cpp
while (auto result = api.step()) {
    // result 的类型为 std::optional<StepResult>
    auto &[msg, frames] = *result;
    // msg: SimCarMsg，frames: std::vector<CameraFrame>
}
```

| 字段 | 类型 | 说明 |
|------|------|------|
| `trajectory` | `std::vector<Vector3>` | 参考轨迹点序列 |
| `pose_gnss` | `PoseGnss` | 车辆位姿（位置 + 速度 + 朝向） |
| `main_vehicle` | `MainVehicleInfo` | 主车状态信息 |
| `sensor` | `SensorInfo` | 传感器配置信息 |
| `obstacles` | `std::vector<ObstacleInfo>` | 场景中的所有障碍物 |
| `traffic_light_groups` | `std::vector<TrafficLightGroupInfo>` | 所有交通灯组 |
| `scene_status` | `SceneStatus` | 当前场景状态 |

---

## PoseGnss

车辆的位姿信息，包含位置、速度和朝向。

| 字段 | 类型 | 说明 |
|------|------|------|
| `pos_x` | `double` | X 坐标 (m) |
| `pos_y` | `double` | Y 坐标 (m) |
| `pos_z` | `double` | Z 坐标（高度）(m) |
| `vel_x` | `double` | X 方向速度分量 (m/s) |
| `vel_y` | `double` | Y 方向速度分量 (m/s) |
| `vel_z` | `double` | Z 方向速度分量 (m/s) |
| `ori_x` | `double` | 朝向 X 分量 (rad) |
| `ori_y` | `double` | 朝向 Y 分量 (rad) |
| `ori_z` | `double` | 朝向 Z 分量（偏航角）(rad) |

```cpp
const auto &pose = msg.pose_gnss;
std::cout << "位置: (" << pose.pos_x << ", " << pose.pos_y << ")\n";
std::cout << "偏航角: " << pose.ori_z << " rad\n";
```

---

## MainVehicleInfo

主车（被控车辆）的详细状态。

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `int` | 主车 ID |
| `speed` | `double` | 车速 (m/s) |
| `gear` | `GearMode` | 当前档位 |
| `throttle` | `double` | 当前油门值 |
| `brake` | `double` | 当前刹车值 |
| `steering` | `double` | 当前方向盘转角 |
| `length` | `double` | 车身长度 (m) |
| `width` | `double` | 车身宽度 (m) |
| `height` | `double` | 车身高度 (m) |
| `left_blinker_on` | `bool` | 左转向灯状态 |
| `right_blinker_on` | `bool` | 右转向灯状态 |
| `hazard_lights_on` | `bool` | 双闪灯状态 |
| `brake_lights_on` | `bool` | 刹车灯状态 |
| `headlights_on` | `bool` | 前照灯状态 |

```cpp
double speed = msg.main_vehicle.speed;
double car_length = msg.main_vehicle.length;
```

---

## SensorInfo

传感器配置信息。

| 字段 | 类型 | 说明 |
|------|------|------|
| `ego_rgb_cams` | `std::vector<CameraInfo>` | 自车 RGB 摄像头列表 |
| `v2x_cams` | `std::vector<CameraInfo>` | V2X 摄像头列表 |

### CameraInfo

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `std::string` | 摄像头 ID |
| `position` | `Vector3` | 安装位置 |
| `orientation` | `EulerAngle` | 安装朝向（欧拉角） |
| `fov` | `double` | 视场角 |
| `intrinsic_matrix` | `std::vector<double>` | 内参矩阵（展平数组） |
| `image_width` | `int` | 图像宽度 (px) |
| `image_height` | `int` | 图像高度 (px) |

### EulerAngle

| 字段 | 类型 | 说明 |
|------|------|------|
| `ori_x` | `double` | 绕 X 轴旋转 (rad) |
| `ori_y` | `double` | 绕 Y 轴旋转 (rad) |
| `ori_z` | `double` | 绕 Z 轴旋转 (rad) |

---

## CameraFrame

`StepResult::frames` 中的每个元素对应一个自车摄像头的图像数据。

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `std::string` | 对应 `CameraInfo::id` |
| `data` | `std::vector<uint8_t>` | JPEG 编码的原始字节 |

```cpp
while (auto result = api.step()) {
    auto &[msg, frames] = *result;
    for (const auto &frame : frames) {
        // frame.id   — 摄像头 ID
        // frame.data — JPEG 字节，可写入文件或自行解码
    }
}
```

!!! note "关于摄像头图像"
    C++ 版 API **不依赖 OpenCV**，摄像头图像以 JPEG 编码的原始字节返回。如需处理图像，可使用 OpenCV、stb_image 等库自行解码。

---

## ObstacleInfo

场景中的障碍物信息（其他车辆、行人、静态物体等）。

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `int` | 障碍物 ID |
| `type` | `ObstacleType` | 障碍物类型 |
| `pos_x` | `double` | X 坐标 (m) |
| `pos_y` | `double` | Y 坐标 (m) |
| `pos_z` | `double` | Z 坐标 (m) |
| `vel_x` | `double` | X 方向速度 (m/s) |
| `vel_y` | `double` | Y 方向速度 (m/s) |
| `vel_z` | `double` | Z 方向速度 (m/s) |
| `ori_x` | `double` | 朝向 X 分量 (rad) |
| `ori_y` | `double` | 朝向 Y 分量 (rad) |
| `ori_z` | `double` | 朝向 Z 分量 (rad) |
| `length` | `double` | 长度 (m) |
| `width` | `double` | 宽度 (m) |
| `height` | `double` | 高度 (m) |
| `extra_info` | `std::optional<std::string>` | 附加信息（可选） |

```cpp
for (const auto &obs : msg.obstacles) {
    if (obs.type == metacar::ObstacleType::CAR) {
        double dist = std::sqrt(
            std::pow(obs.pos_x - pose.pos_x, 2) +
            std::pow(obs.pos_y - pose.pos_y, 2)
        );
        std::cout << "前方车辆距离: " << dist << " m\n";
    }
}
```

障碍物类型详见 [枚举类型 — ObstacleType](enums.md#obstacletype)。

---

## TrafficLightGroupInfo

交通灯组信息。一个路口可能有多组交通灯。

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `std::string` | 灯组 ID |
| `traffic_lights` | `std::vector<TrafficLightInfo>` | 该组中的各个交通灯 |

### TrafficLightInfo

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `std::string` | 交通灯 ID |
| `road_id` | `std::string` | 所属道路 ID |
| `position` | `Vector3` | 位置坐标 |
| `left_state` | `TrafficLightState` | 左转灯状态 |
| `left_remaining_time` | `double` | 左转灯剩余时间 (s) |
| `right_state` | `TrafficLightState` | 右转灯状态 |
| `right_remaining_time` | `double` | 右转灯剩余时间 (s) |
| `straight_state` | `TrafficLightState` | 直行灯状态 |
| `straight_remaining_time` | `double` | 直行灯剩余时间 (s) |

```cpp
for (const auto &group : msg.traffic_light_groups) {
    for (const auto &light : group.traffic_lights) {
        if (light.straight_state == metacar::TrafficLightState::RED) {
            std::cout << "红灯! 剩余 " << light.straight_remaining_time << " s\n";
        }
    }
}
```

交通灯状态详见 [枚举类型 — TrafficLightState](enums.md#trafficlightstate)。

---

## SceneStatus

当前场景/子场景的运行状态。

| 字段 | 类型 | 说明 |
|------|------|------|
| `sub_scene_name` | `std::string` | 当前子场景名称 |
| `used_time` | `double` | 已用时间 (s) |
| `time_limit` | `double` | 时间限制 (s) |
| `end_point` | `std::optional<Vector3>` | 终点位置（可选） |

```cpp
const auto &status = msg.scene_status;
double remaining = status.time_limit - status.used_time;
std::cout << "剩余时间: " << remaining << " s\n";
```
