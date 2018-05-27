#pragma once

#include "../logging.hpp"
#include <cassert>
#include <epoxy/gl.h>
#include <iostream>

namespace flex {
namespace gl {

#define GL_CALL(x)                                                             \
  flex::gl::clear_error();                                                     \
  x;                                                                           \
  assert(flex::gl::log_call(#x, __FILE__, __LINE__));

static inline void clear_error() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

static inline bool log_call(const char *function, const char *file,
                            const int line) {
  while (GLenum error = glGetError()) {
    flex::log(L_ERROR, L_GL,
              "Error (" + std::to_string(error) + "): " + function + " in " +
                  file + " at line " + std::to_string(line));
    return false;
  }
  return true;
}

static inline void clear_color(float r, float g, float b, float a) {
  GL_CALL(glClearColor(r, g, b, a));
}

static inline void clear_buffers() {
  GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

static inline void draw_elements(unsigned int indices_size) {
  GL_CALL(glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0));
}

static inline void draw_elements_instanced(unsigned int indices_size,
                                           unsigned int amount) {
  GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT,
                                  0, amount));
}

} // namespace gl
} // namespace flex
