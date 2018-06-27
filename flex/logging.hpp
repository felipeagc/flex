#pragma once

#include <stdarg.h>

#ifdef NDEBUG
#define FLEX_LOG_DEBUG 0
#else
#define FLEX_LOG_DEBUG 1
#endif

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

const char *log_level_to_string(LogLevel level);
const char *log_type_to_string(LogType type);
void log_print(LogLevel level, LogType type, const char *text, va_list args);

void log(LogLevel level, LogType type, const char *text, ...);
void log(LogLevel level, const char *text, ...);
void log(const char *text, ...);
} // namespace flex
