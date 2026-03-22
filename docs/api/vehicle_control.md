# 车辆控制

## VehicleControl

`VehicleControl` 用于向仿真器发送车辆控制指令，是每帧循环中必须使用的核心结构。

```cpp
metacar::VehicleControl ctrl;
ctrl.throttle = 0.5;
ctrl.gear = metacar::GearMode::DRIVE;
api.set_vehicle_control(ctrl);
```

### 字段

| 字段 | 类型 | 默认值 | 值域 | 说明 |
|------|------|--------|------|------|
| `throttle` | `double` | `0.0` | 0.0 ~ 1.0 | 油门开度。0 为不加油，1 为全油门 |
| `brake` | `double` | `0.0` | 0.0 ~ 1.0 | 刹车力度。0 为不刹车，1 为全力制动 |
| `steering` | `double` | `0.0` | -1.0 ~ 1.0 | 方向盘转角。负值向左，正值向右 |
| `gear` | `GearMode` | `DRIVE` | — | 档位模式 |
| `left_blinker_on` | `bool` | `false` | — | 左转向灯 |
| `right_blinker_on` | `bool` | `false` | — | 右转向灯 |
| `hazard_lights_on` | `bool` | `false` | — | 双闪警示灯 |
| `headlights_on` | `bool` | `false` | — | 前照灯 |

### 使用示例

**基本前进：**

```cpp
metacar::VehicleControl ctrl;
ctrl.gear = metacar::GearMode::DRIVE;
ctrl.throttle = 0.3;
api.set_vehicle_control(ctrl);
```

**转弯 + 转向灯：**

```cpp
metacar::VehicleControl ctrl;
ctrl.gear = metacar::GearMode::DRIVE;
ctrl.throttle = 0.2;
ctrl.steering = -0.3;        // 向左转
ctrl.left_blinker_on = true; // 开左转向灯
api.set_vehicle_control(ctrl);
```

**倒车：**

```cpp
metacar::VehicleControl ctrl;
ctrl.gear = metacar::GearMode::REVERSE;
ctrl.throttle = 0.1;
api.set_vehicle_control(ctrl);
```

**紧急制动：**

```cpp
metacar::VehicleControl ctrl;
ctrl.brake = 1.0;
ctrl.hazard_lights_on = true;
api.set_vehicle_control(ctrl);
```

---

## GearMode

档位模式枚举。

```cpp
enum class GearMode {
    NEUTRAL = 0,   // 空挡
    DRIVE   = 1,   // 前进挡
    REVERSE = 2,   // 倒车挡
    PARKING = 3,   // 驻车挡
};
```

| 值 | 名称 | 说明 |
|----|------|------|
| `NEUTRAL` | 空挡 | 车辆不驱动 |
| `DRIVE` | 前进挡 | 正常行驶 |
| `REVERSE` | 倒车挡 | 倒车行驶 |
| `PARKING` | 驻车挡 | 车辆停放 |

!!! tip "默认档位"
    `VehicleControl` 的 `gear` 默认值为 `GearMode::DRIVE`，大多数情况下无需手动设置。
