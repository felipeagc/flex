#include "vertex_array.hpp"

using namespace flex::gl;

VertexArray::VertexArray() {
  GL_CALL(glGenVertexArrays(1, &m_vao));
}

VertexArray::~VertexArray() {
  GL_CALL(glDeleteVertexArrays(1, &m_vao));
}

void VertexArray::bind() {
  GL_CALL(glBindVertexArray(m_vao));
}

void VertexArray::unbind() {
  GL_CALL(glBindVertexArray(0));
}
