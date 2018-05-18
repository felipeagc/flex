#include "index_buffer.hpp"

using namespace flex::gl;

void IndexBuffer::buffer(const void *indices, const GLuint size) {
  this->bind();
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}

void IndexBuffer::buffer_sub_data(const void *data, const GLuint size,
                                  const GLintptr offset) {
  GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
}

void IndexBuffer::bind() const {
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer));
}

void IndexBuffer::unbind() const {
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
