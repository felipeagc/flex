#pragma once

#include <flex/gl/buffer.hpp>
#include <flex/gl/util.hpp>
#include <glad/glad.h>

namespace flex {
namespace gl {
class IndexBuffer : public Buffer {
public:
  void buffer(const void *indices, const GLuint size) override;
  void buffer_sub_data(const void *data, const GLuint size, const GLintptr offset) override;

  void bind() const override;
  static void unbind();
};
} // namespace gl
} // namespace flex
