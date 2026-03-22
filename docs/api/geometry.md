# 几何类型

MetaCar 提供 `Vector2` 和 `Vector3` 两个基础几何类型，用于表示位置、方向和路径点。

---

## Vector2

二维向量，用于表示平面坐标和路径点。

```cpp
metacar::Vector2 v(3.0, 4.0);
```

### 字段

| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `x` | `double` | `0.0` | X 分量 |
| `y` | `double` | `0.0` | Y 分量 |

### 构造函数

```cpp
Vector2();                     // (0, 0)
Vector2(double x, double y);   // (x, y)
```

### 运算符

| 运算符 | 说明 | 示例 |
|--------|------|------|
| `+` | 向量加法 | `v1 + v2` |
| `-` | 向量减法 / 取反 | `v1 - v2` 或 `-v` |
| `*` | 标量乘法 | `v * 2.0` 或 `2.0 * v` |
| `/` | 标量除法 | `v / 2.0` |

### 方法

#### `rotate_rad(double radians)`

绕原点逆时针旋转指定弧度，返回新向量。

```cpp
metacar::Vector2 v(1.0, 0.0);
auto rotated = v.rotate_rad(M_PI / 2);  // (0, 1)
```

#### `angle_rad()`

返回向量与 X 轴正方向的夹角，范围 [-&pi;, &pi;]。

```cpp
metacar::Vector2 v(1.0, 1.0);
double angle = v.angle_rad();  // ≈ 0.785 (π/4)
```

#### `length()`

返回向量的欧几里得长度。

```cpp
metacar::Vector2 v(3.0, 4.0);
double len = v.length();  // 5.0
```

#### `normalized()`

返回同方向的单位向量。

```cpp
metacar::Vector2 v(3.0, 4.0);
auto unit = v.normalized();  // (0.6, 0.8)
```

---

## Vector3

三维向量，用于表示空间坐标、位置和朝向。

```cpp
metacar::Vector3 v(1.0, 2.0, 3.0);
```

### 字段

| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `x` | `double` | `0.0` | X 分量 |
| `y` | `double` | `0.0` | Y 分量 |
| `z` | `double` | `0.0` | Z 分量 |

### 构造函数

```cpp
Vector3();                                 // (0, 0, 0)
Vector3(double x, double y, double z);     // (x, y, z)
```

### 运算符

与 `Vector2` 相同：`+`、`-`、`*`、`/`。

### 方法

#### `yaw_rad()`

返回在 xOy 平面上投影与 X 轴正方向的夹角（偏航角），范围 [-&pi;, &pi;]。

```cpp
metacar::Vector3 v(1.0, 1.0, 5.0);
double yaw = v.yaw_rad();  // ≈ 0.785 (π/4)，忽略 z 分量
```

#### `to_vector2()`

提取 x、y 分量，返回 `Vector2`。

```cpp
metacar::Vector3 v3(1.0, 2.0, 3.0);
metacar::Vector2 v2 = v3.to_vector2();  // (1.0, 2.0)
```

#### `length()`

返回三维欧几里得长度。

```cpp
metacar::Vector3 v(1.0, 2.0, 2.0);
double len = v.length();  // 3.0
```

#### `normalized()`

返回同方向的单位向量。

```cpp
metacar::Vector3 v(0.0, 0.0, 5.0);
auto unit = v.normalized();  // (0, 0, 1)
```
