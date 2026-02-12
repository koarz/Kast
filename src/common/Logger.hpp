#pragma once

#include <string>

namespace kast {
class Logger {
public:
  static void Init(const std::string &log_file = "./logs/kast.log");
  static void Shutdown();

  static void Info(const char *file, int line, const std::string &msg);
  static void Warn(const char *file, int line, const std::string &msg);
  static void Error(const char *file, int line, const std::string &msg);
  static void Debug(const char *file, int line, const std::string &msg);
};
} // namespace kast

#include "fmt/format.h"

#define LOG_INFO(...)                                                          \
  kast::Logger::Info(__FILE__, __LINE__, fmt::format(__VA_ARGS__))
#define LOG_WARN(...)                                                          \
  kast::Logger::Warn(__FILE__, __LINE__, fmt::format(__VA_ARGS__))
#define LOG_ERROR(...)                                                         \
  kast::Logger::Error(__FILE__, __LINE__, fmt::format(__VA_ARGS__))
#define LOG_DEBUG(...)                                                         \
  kast::Logger::Debug(__FILE__, __LINE__, fmt::format(__VA_ARGS__))
