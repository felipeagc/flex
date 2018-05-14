#pragma once

#include <glad/glad.h>

namespace flex {
namespace gl {
class VertexBuffer {
public:
  VertexBuffer();
  ~VertexBuffer();

  void buffer(const void* data, const GLuint size);
  void bind();
  void unbind();

private:
  GLuint m_vbo;
};
} // namespace gl
} // namespace flex
