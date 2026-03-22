# 场景静态数据

场景静态数据在 `connect()` 后加载，整个仿真过程中不变。通过 `get_scene_static_data()` 获取。

```cpp
const auto &data = api.get_scene_static_data();
```

---

## SceneStaticData

| 字段 | 类型 | 说明 |
|------|------|------|
| `route` | `std::vector<Vector3>` | 规划路线的路径点序列 |
| `roads` | `std::vector<RoadInfo>` | 场景中的所有道路 |
| `sub_scenes` | `std::vector<SubSceneInfo>` | 子场景列表 |
| `vla_extension` | `std::optional<VLAExtension>` | VLA 扩展数据（可选） |

```cpp
// 遍历路线点
for (const auto &pt : data.route) {
    std::cout << "(" << pt.x << ", " << pt.y << ")\n";
}

// 查看子场景数量
std::cout << "子场景数量: " << data.sub_scenes.size() << "\n";
```

---

## RoadInfo

道路信息，包含车道数据和连接关系。

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `std::string` | 道路 ID |
| `begin_pos` | `Vector3` | 道路起点坐标 |
| `end_pos` | `Vector3` | 道路终点坐标 |
| `driving_type` | `DrivingType` | 允许通行的类型 |
| `traffic_sign_type` | `TrafficSignType` | 交通标志类型 |
| `stop_line` | `std::vector<Vector2>` | 停止线点序列 |
| `predecessor_ids` | `std::vector<std::string>` | 前驱道路 ID 列表 |
| `successor_ids` | `std::vector<std::string>` | 后继道路 ID 列表 |
| `lanes` | `std::vector<LaneInfo>` | 车道列表 |

```cpp
for (const auto &road : data.roads) {
    std::cout << "道路 " << road.id
              << "：" << road.lanes.size() << " 条车道\n";
}
```

---

## LaneInfo

车道信息，包含边界、宽度和相邻车道关系。

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | `std::string` | 车道 ID |
| `left_border` | `BorderInfo` | 左边界 |
| `right_border` | `BorderInfo` | 右边界 |
| `left_lane_id` | `std::string` | 左相邻车道 ID（空字符串表示无） |
| `right_lane_id` | `std::string` | 右相邻车道 ID（空字符串表示无） |
| `width` | `double` | 车道宽度 (m) |
| `path_points` | `std::vector<Vector2>` | 车道中心线点序列 |

---

## BorderInfo

车道边界信息。

| 字段 | 类型 | 说明 |
|------|------|------|
| `type` | `LineType` | 边界线类型 |
| `path_points` | `std::vector<Vector2>` | 边界线点序列 |

边界线类型详见 [枚举类型 — LineType](enums.md#linetype)。

---

## SubSceneInfo

子场景信息。一个完整场景可包含多个子场景。

| 字段 | 类型 | 说明 |
|------|------|------|
| `name` | `std::string` | 子场景名称 |
| `start_point` | `std::optional<Vector3>` | 起点坐标（可选） |
| `end_point` | `std::optional<Vector3>` | 终点坐标（可选） |

```cpp
for (const auto &sub : data.sub_scenes) {
    std::cout << "子场景: " << sub.name << "\n";
    if (sub.end_point) {
        std::cout << "  终点: (" << sub.end_point->x
                  << ", " << sub.end_point->y << ")\n";
    }
}
```
