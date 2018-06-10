#pragma once

#include "buffer.hpp"
#include "gl.hpp"
#include "vertex_buffer_layout.hpp"

namespace flex {
namespace gl {
class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void bind() const;
  static void unbind();

  void add_buffer(const Buffer &vb, const VertexBufferLayout &layout,
                  bool instanced = false);

  void destroy();

private:
  GLuint m_vao;
};
} // namespace gl
} // namespace flex
