#pragma once

#include "gl.hpp"

namespace flex {
namespace gl {
enum BindTarget {
  ARRAY_BUFFER = GL_ARRAY_BUFFER,
  ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
};

class Buffer {
public:
  Buffer();
  ~Buffer();

  void buffer(BindTarget target, const void *data, const GLuint size);
  void buffer_sub_data(BindTarget target, const void *data, const GLuint size,
                       const GLintptr offset);

  void bind(BindTarget target) const;
  static void unbind(BindTarget target);

  void destroy();

protected:
  GLuint m_buffer;
};
} // namespace gl
} // namespace flex
