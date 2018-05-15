#include "index_buffer.hpp"

using namespace flex::gl;

IndexBuffer::IndexBuffer() {
  GL_CALL(glGenBuffers(1, &m_ebo));
}

IndexBuffer::~IndexBuffer() {
  GL_CALL(glDeleteBuffers(1, &m_ebo));
}


void IndexBuffer::buffer(const void *indices, const GLuint size) {
  this->bind();
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW)); 
}

void IndexBuffer::bind() {
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
}

void IndexBuffer::unbind() {
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
