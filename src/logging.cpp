#include "metacar/logging.hpp"

#include <iostream>
#include <mutex>

namespace metacar {

static LogLevel g_level = LogLevel::INFO;
static LogCallback g_callback = [](LogLevel level, const std::string &msg) {
  static const char *tags[] = {"DEBUG", "INFO", "WARN", "ERROR"};
  std::cerr << "[metacar] " << tags[static_cast<int>(level)] << ": " << msg << std::endl;
};
static std::mutex g_mutex;

void set_log_callback(LogCallback cb) {
  std::lock_guard lock(g_mutex);
  g_callback = std::move(cb);
}

void set_log_level(LogLevel level) { g_level = level; }

namespace detail {
void log(LogLevel level, const std::string &msg) {
  if (level < g_level)
    return;
  std::lock_guard lock(g_mutex);
  if (g_callback)
    g_callback(level, msg);
}
} // namespace detail

} // namespace metacar
