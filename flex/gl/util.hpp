#pragma once

#include "../logging.hpp"
#include "gl.hpp"
#include <cassert>
#include <iostream>

namespace flex {
namespace gl {

#define GL_CALL(x)                                                             \
  flex::gl::glClearError();                                                    \
  x;                                                                           \
  assert(flex::gl::glLogCall(#x, __FILE__, __LINE__));

static inline void glClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

static inline bool glLogCall(const char *function, const char *file,
                             const int line) {
  while (GLenum error = glGetError()) {
    flex::log(L_ERROR, L_GL,
              "Error (" + std::to_string(error) + "): " + function + " in " +
                  file + " at line " + std::to_string(line));
    return false;
  }
  return true;
}

} // namespace gl
} // namespace flex
