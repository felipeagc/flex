#include "vertex_buffer.hpp"
#include <glad/glad.h>

using namespace flex::gl;

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &m_vbo);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_vbo);
}

void VertexBuffer::buffer(const void* data, const GLuint size) {
  this->bind();
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VertexBuffer::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
