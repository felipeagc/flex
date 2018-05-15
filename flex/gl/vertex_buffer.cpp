#include "vertex_buffer.hpp"

using namespace flex::gl;

VertexBuffer::VertexBuffer() { GL_CALL(glGenBuffers(1, &m_vbo)); }

VertexBuffer::~VertexBuffer() { GL_CALL(glDeleteBuffers(1, &m_vbo)); }

void VertexBuffer::buffer(const void *data, const GLuint size, bool dynamic) {
  this->bind();

  auto usage = dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

void VertexBuffer::bind() const {
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
}

void VertexBuffer::unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
