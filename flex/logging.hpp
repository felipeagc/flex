#pragma once

#include <iostream>
#include <string>

#define FLEX_LOG_DEBUG 0
#define FLEX_LOG_INFO 1
#define FLEX_LOG_WARN 1
#define FLEX_LOG_ERROR 1

namespace flex {
enum LogType {
  L_NONE,
  L_GL,
  L_AUDIO,
  L_WINDOW,
  L_RENDER,
  L_IMPORT,
  L_APP,
};

enum LogLevel {
  L_INFO,
  L_DEBUG,
  L_WARN,
  L_ERROR,
};

inline std::string log_level_to_string(LogLevel level) {
  switch (level) {
  case L_INFO:
    return "[INFO]";
    break;
  case L_DEBUG:
    return "[DEBUG]";
    break;
  case L_WARN:
    return "[WARN]";
    break;
  case L_ERROR:
    return "[ERROR]";
    break;
  }
  return "";
}

inline std::string log_type_to_string(LogType type) {
  switch (type) {
  case L_NONE:
    return "";
    break;
  case L_GL:
    return "[GL]";
    break;
  case L_AUDIO:
    return "[AUDIO]";
    break;
  case L_WINDOW:
    return "[WINDOW]";
    break;
  case L_RENDER:
    return "[RENDER]";
    break;
  case L_IMPORT:
    return "[IMPORT]";
    break;
  case L_APP:
    return "[APP]";
    break;
  }
  return "";
}

inline void log_print(const std::string &text, LogLevel level = L_INFO,
                      LogType type = L_APP) {
  if (level == L_INFO && !FLEX_LOG_INFO)
    return;
  if (level == L_DEBUG && !FLEX_LOG_DEBUG)
    return;
  if (level == L_WARN && !FLEX_LOG_WARN)
    return;
  if (level == L_ERROR && !FLEX_LOG_ERROR)
    return;
  std::cout << log_level_to_string(level) << log_type_to_string(type) << " "
            << text << std::endl;
}

inline void log(LogLevel level, LogType type, const std::string &text) {
  log_print(text, level, type);
}

inline void log(LogLevel level, const std::string &text) {
  log_print(text, level, L_APP);
}

inline void log(const std::string &text) { log_print(text, L_INFO, L_APP); }
} // namespace flex
