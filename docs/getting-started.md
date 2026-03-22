# 环境搭建

## 系统要求

| 要求 | 说明 |
|------|------|
| C++ 标准 | C++20 |
| CMake | 3.20 或更高版本 |
| 编译器 | MSVC 19.29+（VS 2019+）或 GCC 10+ / Clang 12+ |
| 平台 | Windows 10/11 或 Linux |

## 构建 metacar 库

metacar 提供了 CMake Presets，可以一键完成配置和构建。

=== "Windows"

    在 **Visual Studio Developer Terminal** 中执行：

    ```bash
    cmake --preset win-debug
    cmake --build --preset win-debug
    ```

    !!! note "为什么要用 Developer Terminal？"
        需要确保 `cl.exe`（MSVC 编译器）在 PATH 中。普通终端找不到 MSVC 编译器会导致配置失败。

=== "Linux"

    ```bash
    cmake --preset linux-debug
    cmake --build --preset linux-debug
    ```

构建产物为**静态库**（`metacar.lib` / `libmetacar.a`）。

## 在你的项目中使用 metacar

### CMake 集成

在你的项目的 `CMakeLists.txt` 中添加：

```cmake
find_package(metacar REQUIRED)
target_link_libraries(your_app PRIVATE metacar::metacar)
```

然后在代码中 include 总入口头文件即可：

```cpp
#include "metacar/metacar.hpp"
```

### 设置 CMAKE_PREFIX_PATH

你需要告诉 CMake 去哪里找 metacar。有两种方式：

**方式一：配置时指定**

```bash
cmake -B build -DCMAKE_PREFIX_PATH=/path/to/metacar/install
```

**方式二：使用 FetchContent 直接引入源码**

```cmake
include(FetchContent)
FetchContent_Declare(
  metacar
  GIT_REPOSITORY <metacar 仓库地址>
  GIT_TAG master
)
FetchContent_MakeAvailable(metacar)

target_link_libraries(your_app PRIVATE metacar::metacar)
```

## 依赖说明

| 依赖 | 版本 | 获取方式 |
|------|------|----------|
| nlohmann_json | 3.12.0 | CMake FetchContent 自动拉取 |
| Winsock2 (ws2_32) | — | Windows 系统自带 |
| POSIX sockets | — | Linux 系统自带 |

你**不需要**手动安装任何第三方库。

## 验证安装

创建一个最小测试程序：

```cpp
#include "metacar/metacar.hpp"
#include <iostream>

int main() {
    metacar::SceneAPI api;
    std::cout << "MetaCar API ready.\n";
    return 0;
}
```

如果编译链接通过，说明安装成功。
