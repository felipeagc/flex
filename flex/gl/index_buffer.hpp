#pragma once

#include <glad/glad.h>
#include <flex/gl/util.hpp>

namespace flex {
namespace gl {
class IndexBuffer {
public:
  IndexBuffer();
  ~IndexBuffer();

  void buffer(const void *indices, const GLuint size);

  void bind();
  void unbind();

private:
  GLuint m_ebo;
};
} // namespace gl
} // namespace flex
