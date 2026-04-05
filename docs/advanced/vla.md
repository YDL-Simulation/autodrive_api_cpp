# VLA 场景

VLA（Vision-Language-Action）是一类特殊的仿真场景，需要在控制车辆的同时完成额外的感知与决策任务，如指令识别、违停检测、合规性检查等。

## 概述

普通场景只需要发送 `VehicleControl` 即可。VLA 场景还需要在 `set_vehicle_control()` 中附加 `VLAExtensionOutput`，向仿真器提交感知结果。

```cpp
metacar::VehicleControl ctrl;
ctrl.throttle = 0.3;
ctrl.gear = metacar::GearMode::DRIVE;

metacar::VLAExtensionOutput vla_output;
// ... 填充感知结果 ...

api.set_vehicle_control(ctrl, vla_output);
```

## 判断是否为 VLA 场景

VLA 场景在静态数据中包含 `vla_extension` 字段：

```cpp
const auto &data = api.get_scene_static_data();
if (data.vla_extension) {
    // 这是 VLA 场景
    const auto &ext = *data.vla_extension;
    // 可以访问 ext.buildings 和 ext.regions
}
```

---

## 输入数据

VLA 场景的静态数据通过 `SceneStaticData::vla_extension` 提供。

### VLAExtension

| 字段 | 类型 | 说明 |
|------|------|------|
| `buildings` | `std::vector<BuildingInfo>` | 场景中的建筑物列表 |
| `regions` | `std::vector<RegionInfo>` | 场景中的区域列表 |

### BuildingInfo

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `std::string` | 建筑物 ID |
| `name` | `std::string` | 显示名称 |
| `pos_x` | `double` | X 坐标 (m) |
| `pos_y` | `double` | Y 坐标 (m) |
| `pos_z` | `double` | Z 坐标 (m) |
| `ori_x` | `double` | 朝向 X (rad) |
| `ori_y` | `double` | 朝向 Y (rad) |
| `ori_z` | `double` | 朝向 Z (rad) |
| `length` | `double` | 长度 (m) |
| `width` | `double` | 宽度 (m) |
| `height` | `double` | 高度 (m) |

### RegionInfo

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `std::string` | 区域 ID |
| `type` | `RegionType` | 区域类型 |
| `pos_x` | `double` | X 坐标 (m) |
| `pos_y` | `double` | Y 坐标 (m) |
| `pos_z` | `double` | Z 坐标 (m) |
| `ori_x` | `double` | 朝向 X (rad) |
| `ori_y` | `double` | 朝向 Y (rad) |
| `ori_z` | `double` | 朝向 Z (rad) |
| `length` | `double` | 长度 (m) |
| `width` | `double` | 宽度 (m) |

区域类型详见 [枚举类型 — RegionType](../api/enums.md#regiontype)。

---

## 输出数据

VLA 场景需要提交的感知结果通过 `VLAExtensionOutput` 传递。

### VLAExtensionOutput

| 字段 | 类型 | 说明 |
|------|------|------|
| `text_info` | `std::optional<VLATextOutput>` | 文本识别结果 |
| `function_zone_result` | `std::optional<FunctionZoneResult>` | 功能区检测结果 |
| `parking_result` | `std::optional<ParkingResult>` | 停车检测结果 |

所有字段均为可选，根据具体子场景的要求填充对应字段。

### VLATextOutput

文本/指令识别结果。

| 字段 | 类型 | 说明 |
|------|------|------|
| `ocr_text` | `std::string` | OCR 识别的原始文本 |
| `time_phrase` | `std::string` | 提取的时间短语 |
| `location_phrase` | `std::string` | 提取的地点短语 |
| `action_phrase` | `std::string` | 提取的动作短语 |

### FunctionZoneResult

功能区合规检测结果。

| 字段 | 类型 | 说明 |
|------|------|------|
| `violations` | `std::vector<FunctionZoneViolation>` | 违规列表 |

### FunctionZoneViolation

| 字段 | 类型 | 说明 |
|------|------|------|
| `rule_code` | `std::string` | 违规规则编码 |
| `sticker_ids` | `std::vector<std::string>` | 涉及的贴纸 ID 列表 |

### ParkingResult

停车违规检测结果。

| 字段 | 类型 | 说明 |
|------|------|------|
| `violating_sticker_ids` | `std::vector<std::string>` | 违规停车的贴纸 ID 列表 |

---

## 使用示例

```cpp
const auto &data = api.get_scene_static_data();

while (auto result = api.step()) {
    auto &[msg, frames] = *result;
    metacar::VehicleControl ctrl;
    ctrl.gear = metacar::GearMode::DRIVE;
    ctrl.throttle = 0.2;

    if (data.vla_extension) {
        // VLA 场景：附加感知结果
        metacar::VLAExtensionOutput vla_output;

        // 示例：提交文本识别结果
        metacar::VLATextOutput text;
        text.ocr_text = "前方200米左转";
        text.action_phrase = "左转";
        text.location_phrase = "前方200米";
        vla_output.text_info = text;

        api.set_vehicle_control(ctrl, vla_output);
    } else {
        // 普通场景
        api.set_vehicle_control(ctrl);
    }
}
```
