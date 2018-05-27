#pragma once

#include "buffer.hpp"
#include "gl.hpp"

namespace flex {
namespace gl {
class VertexBuffer : public Buffer {
public:
  void buffer(const void *data, const GLuint size);
  void buffer_sub_data(const void *data, const GLuint size,
                       const GLintptr offset);

  void bind() const;
  static void unbind();
};
} // namespace gl
} // namespace flex
