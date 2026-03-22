#pragma once

#include <functional>
#include <string>

namespace metacar {

enum class LogLevel { DBG, INFO, WARN, ERR };

using LogCallback = std::function<void(LogLevel, const std::string &)>;

/// Set custom log handler. Pass nullptr to disable logging.
void set_log_callback(LogCallback cb);

/// Set minimum log level (default: INFO).
void set_log_level(LogLevel level);

namespace detail {
void log(LogLevel level, const std::string &msg);
} // namespace detail

} // namespace metacar
