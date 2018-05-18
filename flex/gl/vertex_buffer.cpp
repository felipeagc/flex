#include "vertex_buffer.hpp"

using namespace flex::gl;

void VertexBuffer::buffer(const void *data, const GLuint size) {
  this->bind();

  GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::buffer_sub_data(const void *data, const GLuint size,
                                   const GLintptr offset) {
  GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void VertexBuffer::bind() const {
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer));
}

void VertexBuffer::unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
