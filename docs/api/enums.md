# 枚举类型

本页汇总 MetaCar 中所有枚举类型。

---

## GearMode

档位模式。详见 [车辆控制](vehicle_control.md)。

| 值 | 名称 | 说明 |
|----|------|------|
| 0 | `NEUTRAL` | 空挡 |
| 1 | `DRIVE` | 前进挡 |
| 2 | `REVERSE` | 倒车挡 |
| 3 | `PARKING` | 驻车挡 |

---

## ObstacleType

障碍物类型，标识场景中各种物体的类别。

| 值 | 名称 | 说明 |
|----|------|------|
| 0 | `UNKNOWN` | 未知类型 |
| 4 | `PEDESTRIAN` | 行人 |
| 6 | `CAR` | 小汽车 |
| 7 | `STATIC` | 静态障碍物 |
| 8 | `BICYCLE` | 自行车 |
| 12 | `ROAD_MARK` | 道路标线 |
| 13 | `TRAFFIC_SIGN` | 交通标志 |
| 15 | `TRAFFIC_LIGHT` | 交通灯 |
| 17 | `RIDER` | 骑行者 |
| 18 | `TRUCK` | 卡车 |
| 19 | `BUS` | 公交车 |
| 20 | `SPECIAL_VEHICLE` | 特种车辆 |
| 21 | `MOTORCYCLE` | 摩托车 |
| 22 | `DYNAMIC` | 动态障碍物 |
| 26 | `SPEED_LIMIT_SIGN` | 限速标志 |
| 27 | `BICYCLE_STATIC` | 静态自行车 |
| 29 | `ROAD_OBSTACLE` | 道路障碍 |
| 30 | `PARKING_SLOT` | 停车位 |

```cpp
if (obs.type == metacar::ObstacleType::PEDESTRIAN) {
    // 处理行人
}
```

---

## TrafficLightState

交通灯状态。

| 值 | 名称 | 说明 |
|----|------|------|
| 1 | `RED` | 红灯 |
| 2 | `GREEN` | 绿灯 |
| 3 | `YELLOW` | 黄灯 |

---

## LineType

道路线类型，用于车道边界。

| 值 | 名称 | 说明 |
|----|------|------|
| 1 | `MIDDLE_LINE` | 中间线 |
| 2 | `SIDE_LINE` | 侧边线 |
| 3 | `SOLID_LINE` | 实线 |
| 4 | `STOP_LINE` | 停止线 |
| 5 | `ZEBRA_CROSSING` | 斑马线 |
| 6 | `DASH_LINE` | 虚线 |

---

## DrivingType

道路允许通行的交通参与者类型。

| 值 | 名称 | 说明 |
|----|------|------|
| 1 | `MOTOR_VEHICLE_ALLOWED` | 允许机动车通行 |
| 2 | `NON_MOTOR_VEHICLE_ALLOWED` | 允许非机动车通行 |
| 3 | `PEDESTRIAN_ALLOWED` | 允许行人通行 |

---

## TrafficSignType

交通标志类型。

| 值 | 名称 | 说明 |
|----|------|------|
| 0 | `NO_SIGN` | 无标志 |
| 1 | `SPEED_LIMIT_SIGN` | 限速标志 |
| 2 | `STOP_SIGN` | 停车标志 |
| 3 | `V2X_SIGN` | V2X 标志 |

---

## RegionType

区域类型，用于 VLA 场景。详见 [VLA 场景](../advanced/vla.md)。

| 值 | 名称 | 说明 |
|----|------|------|
| 0 | `NORMAL_PARKING` | 普通停车区 |
| 1 | `RESTRICTED_PARKING` | 限制停车区 |
| 2 | `FUNCTION_ZONE` | 功能区 |
