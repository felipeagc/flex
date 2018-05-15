#pragma once

#include "util.hpp"
#include <glad/glad.h>

namespace flex {
namespace gl {
class VertexBuffer {
public:
  VertexBuffer();
  ~VertexBuffer();

  void buffer(const void *data, const GLuint size, bool dynamic = false);
  void bind() const;
  void unbind() const;

private:
  GLuint m_vbo;
};
} // namespace gl
} // namespace flex
