#pragma once

#include "gl.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"

namespace flex {
namespace gl {
class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void bind() const;
  static void unbind();

  void add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout,
                  bool instanced = false);

private:
  GLuint m_vao;
  unsigned int m_attrib_count = 0;
};
} // namespace gl
} // namespace flex
