#include "vertex_array.hpp"

using namespace flex::gl;

VertexArray::VertexArray() {
  glGenVertexArrays(1, &m_vao);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &m_vao);
}

void VertexArray::bind() {
  glBindVertexArray(m_vao);
}

void VertexArray::unbind() {
  glBindVertexArray(0);
}
