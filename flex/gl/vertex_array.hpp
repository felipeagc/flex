#pragma once

#include <glad/glad.h>
#include "util.hpp"

namespace flex {
namespace gl {
class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void bind();
  void unbind();

private:
  GLuint m_vao;
};
} // namespace gl
} // namespace flex
