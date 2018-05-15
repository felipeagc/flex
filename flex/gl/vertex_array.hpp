#pragma once

#include "util.hpp"
#include "vertex_buffer.hpp"
#include "vertex_layout.hpp"
#include <glad/glad.h>

namespace flex {
namespace gl {
class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void bind();
  void unbind();

  void set_buffer(const VertexBuffer &vb, const VertexLayout &layout);

private:
  GLuint m_vao;
};
} // namespace gl
} // namespace flex
