#pragma once

#include "buffer.hpp"
#include "util.hpp"
#include "gl.hpp"

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
