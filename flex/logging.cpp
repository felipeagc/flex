#include "logging.hpp"

#include <stdarg.h>
#include <stdio.h>

using namespace flex;

const char* flex::log_level_to_string(LogLevel level) {
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

const char *flex::log_type_to_string(LogType type) {
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

void flex::log_print(LogLevel level, LogType type, const char *text,
                             va_list args) {
  if (level == L_INFO && !FLEX_LOG_INFO)
    return;
  if (level == L_DEBUG && !FLEX_LOG_DEBUG)
    return;
  if (level == L_WARN && !FLEX_LOG_WARN)
    return;
  if (level == L_ERROR && !FLEX_LOG_ERROR)
    return;

  printf("%s%s ", flex::log_level_to_string(level), flex::log_type_to_string(type));
  vprintf(text, args);
  printf("\n");
}

void flex::log(LogLevel level, LogType type, const char *text, ...) {
  va_list args;
  va_start(args, text);

  flex::log_print(level, type, text, args);

  va_end(args);
}

void flex::log(LogLevel level, const char *text, ...) {
  va_list args;
  va_start(args, text);

  flex::log_print(level, L_APP, text, args);

  va_end(args);
}

void flex::log(const char *text, ...) {
  va_list args;
  va_start(args, text);

  flex::log_print(L_INFO, L_APP, text, args);

  va_end(args);
}
