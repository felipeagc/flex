#pragma once

#include "util.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include <glad/glad.h>

namespace flex {
namespace gl {
class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void bind();
  void unbind();

  void add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

private:
  GLuint m_vao;
  unsigned int m_attrib_count = 0;
};
} // namespace gl
} // namespace flex
