#pragma once

#include <flex/config.hpp>
#include <string>

namespace flex {
  static inline std::string path(const std::string& file_path) {
    return FLEX_RES_PATH "/" + file_path;
  }
}
