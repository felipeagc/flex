#include "vertex_array.hpp"

using namespace flex::gl;

VertexArray::VertexArray() { GL_CALL(glGenVertexArrays(1, &m_vao)); }

VertexArray::~VertexArray() { GL_CALL(glDeleteVertexArrays(1, &m_vao)); }

void VertexArray::bind() { GL_CALL(glBindVertexArray(m_vao)); }

void VertexArray::unbind() { GL_CALL(glBindVertexArray(0)); }

void VertexArray::set_buffer(const VertexBuffer &vb,
                             const VertexLayout &layout) {
  this->bind();
  vb.bind();
  const auto &elements = layout.get_elements();
  unsigned long int offset = 0;

  for (unsigned int i = 0; i < elements.size(); i++) {
    GL_CALL(glEnableVertexAttribArray(i));
    GL_CALL(glVertexAttribPointer(i, elements[i].count, elements[i].type,
                                  elements[i].normalized, layout.get_stride(),
                                  (const void *)offset));
    offset +=
        elements[i].count * VertexElement::get_size_of_type(elements[i].type);
  }
}
