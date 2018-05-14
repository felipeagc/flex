#pragma once

#include <cassert>
#include <glad/glad.h>
#include <iostream>

#define GL_CALL(x)                                                             \
  flex::gl::glClearError();                                               \
  x;                                                                           \
  assert(flex::gl::glLogCall(#x, __FILE__, __LINE__));

namespace flex {
namespace gl {

static void glClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

static bool glLogCall(const char *function, const char *file, const int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] (" << error << "): " << function << " in "
              << file << " at line " << line << std::endl;
    return false;
  }
  return true;
}

} // namespace gl
} // namespace flex
