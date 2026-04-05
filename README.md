# MetaCar C++ API

自动驾驶仿真 C++ API 库，为元动力仿真平台提供场景管理与车辆控制接口。

## 快速一览

```cpp
#include "metacar/metacar.hpp"

int main() {
    metacar::SceneAPI api;
    api.connect();

    while (auto result = api.step()) {
        auto &[msg, frames] = *result;
        double speed = msg.main_vehicle.speed;

        metacar::VehicleControl ctrl;
        ctrl.throttle = 0.3;
        ctrl.gear = metacar::GearMode::DRIVE;
        api.set_vehicle_control(ctrl);
    }
}
```

## 快速开始

克隆[示例仓库](https://github.com/YDL-Simulation/autodrive_examples_cpp)并构建：

```bash
git clone https://github.com/YDL-Simulation/autodrive_examples_cpp.git
cd autodrive_examples_cpp
cmake -B build
cmake --build build
```

> **Windows 用户**：请在 Visual Studio Developer Terminal 中执行，确保 `cl.exe` 在 PATH 中。

## 集成到已有项目

```cmake
include(FetchContent)
FetchContent_Declare(
  metacar
  GIT_REPOSITORY https://github.com/YDL-Simulation/autodrive_api_cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(metacar)

target_link_libraries(your_app PRIVATE metacar)
```

## 系统要求

| 要求 | 说明 |
|------|------|
| C++ 标准 | C++20 |
| CMake | 3.14+ |
| 编译器 | MSVC 19.29+（VS 2019+）/ GCC 10+ / Clang 12+ |
| 平台 | Windows 10/11、Linux |

唯一依赖 [nlohmann/json](https://github.com/nlohmann/json)，由 CMake FetchContent 自动拉取。

## 文档

完整 API 文档：https://YDL-Simulation.github.io/autodrive_api_cpp/

## 许可证

本项目仅供教学使用。
