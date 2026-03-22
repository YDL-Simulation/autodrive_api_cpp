# 环境搭建

## 系统要求

| 要求 | 说明 |
|------|------|
| C++ 标准 | C++20 |
| CMake | 3.14 或更高版本 |
| 编译器 | MSVC 19.29+（VS 2019+）或 GCC 10+ / Clang 12+ |
| 平台 | Windows 10/11 或 Linux |

## 快速开始（推荐）

最快的方式是直接克隆**示例仓库**，它会通过 CMake FetchContent 自动拉取 metacar 库，无需手动下载任何依赖：

```bash
git clone https://github.com/YDL-Simulation/autodrive_examples_cpp.git
cd autodrive_examples_cpp
```

构建：

=== "Windows"

    在 **Visual Studio Developer Terminal** 中执行：

    ```bash
    cmake -B build
    cmake --build build
    ```

    !!! note "为什么要用 Developer Terminal？"
        需要确保 `cl.exe`（MSVC 编译器）在 PATH 中。普通终端找不到 MSVC 编译器会导致配置失败。

=== "Linux"

    ```bash
    cmake -B build
    cmake --build build
    ```

构建完成后，可执行文件位于 `build/src/` 目录。运行前请先启动仿真器。

!!! tip "项目结构"
    项目结构很简单，直接在 `src/main.cpp` 中编写你的代码：

    ```
    autodrive_examples_cpp/
      CMakeLists.txt      ← 顶层配置，自动拉取 metacar
      src/
        CMakeLists.txt    ← 构建配置
        main.cpp          ← 在这里编写你的代码
    ```

---

## 手动集成（进阶）

如果你已有自己的 CMake 项目，可以通过 FetchContent 引入 metacar：

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

然后在代码中 include 总入口头文件即可：

```cpp
#include "metacar/metacar.hpp"
```

## 依赖说明

| 依赖 | 版本 | 获取方式 |
|------|------|----------|
| nlohmann_json | 3.12.0 | CMake FetchContent 自动拉取 |
| Winsock2 (ws2_32) | — | Windows 系统自带 |
| POSIX sockets | — | Linux 系统自带 |

你**不需要**手动安装任何第三方库，CMake 会自动处理一切。
