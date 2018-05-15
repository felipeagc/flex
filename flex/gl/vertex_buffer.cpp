#include "vertex_buffer.hpp"

using namespace flex::gl;

VertexBuffer::VertexBuffer() { GL_CALL(glGenBuffers(1, &m_vbo)); }

VertexBuffer::~VertexBuffer() { GL_CALL(glDeleteBuffers(1, &m_vbo)); }

void VertexBuffer::buffer(const void *data, const GLuint size) {
  this->bind();
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::bind() const {
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
}

void VertexBuffer::unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
