# 日志

MetaCar 提供了简单的日志接口，支持自定义日志回调和日志级别过滤。

```cpp
#include "metacar/metacar.hpp"
```

---

## LogLevel

日志级别枚举，从低到高：

| 值 | 名称 | 说明 |
|----|------|------|
| `DBG` | 调试 | 详细的调试信息 |
| `INFO` | 信息 | 一般运行信息 |
| `WARN` | 警告 | 潜在问题警告 |
| `ERR` | 错误 | 错误信息 |

!!! note "命名说明"
    使用 `DBG` 和 `ERR` 而非 `DEBUG` 和 `ERROR`，是为了避免与 Windows 头文件中的同名宏冲突。

---

## set_log_level()

```cpp
void metacar::set_log_level(metacar::LogLevel level);
```

设置最低日志级别。低于此级别的日志将被忽略。

- 默认级别：`LogLevel::INFO`

```cpp
// 开启调试日志
metacar::set_log_level(metacar::LogLevel::DBG);

// 只显示警告和错误
metacar::set_log_level(metacar::LogLevel::WARN);
```

---

## set_log_callback()

```cpp
using LogCallback = std::function<void(metacar::LogLevel, const std::string &)>;

void metacar::set_log_callback(LogCallback cb);
```

设置自定义日志处理回调。传入 `nullptr` 可禁用日志输出。

### 示例：输出到控制台

```cpp
metacar::set_log_callback([](metacar::LogLevel level, const std::string &msg) {
    const char *tag = "???";
    switch (level) {
        case metacar::LogLevel::DBG:  tag = "DBG";  break;
        case metacar::LogLevel::INFO: tag = "INFO"; break;
        case metacar::LogLevel::WARN: tag = "WARN"; break;
        case metacar::LogLevel::ERR:  tag = "ERR";  break;
    }
    std::cout << "[" << tag << "] " << msg << "\n";
});
```

### 示例：输出到文件

```cpp
#include <fstream>

std::ofstream log_file("metacar.log");

metacar::set_log_callback([&log_file](metacar::LogLevel level, const std::string &msg) {
    log_file << static_cast<int>(level) << " | " << msg << "\n";
});
```

### 示例：禁用日志

```cpp
metacar::set_log_callback(nullptr);
```

---

## 库内部日志

MetaCar 内部在以下时机输出日志：

| 级别 | 场景 |
|------|------|
| `INFO` | 仿真结束（收到结束信号） |
| `INFO` | 调用 `retry_level()` |
| `INFO` | 调用 `skip_level()` |
| `WARN` | 收到未知消息类型 |
| `ERR` | 连接意外断开 |
