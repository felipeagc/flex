#pragma once

#include "util.hpp"
#include "gl.hpp"

namespace flex {
namespace gl {
class Buffer {
public:
  Buffer();
  virtual ~Buffer();

  virtual void buffer(const void *data, const GLuint size) = 0;
  virtual void buffer_sub_data(const void *data, const GLuint size, const GLintptr offset) = 0;

  virtual void bind() const = 0;
  static void unbind();

protected:
  GLuint m_buffer;
};
} // namespace gl
} // namespace flex
