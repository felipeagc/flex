#pragma once

#include <flex/gl/buffer.hpp>
#include <flex/gl/util.hpp>
#include <glad/glad.h>

namespace flex {
namespace gl {
class VertexBuffer : public Buffer {
public:
  void buffer(const void *data, const GLuint size);
  void buffer_sub_data(const void *data, const GLuint size,
                       const GLintptr offset);

  void bind() const;
  void unbind() const;
};
} // namespace gl
} // namespace flex
