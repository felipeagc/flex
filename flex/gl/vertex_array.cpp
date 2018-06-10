#include "vertex_array.hpp"

using namespace flex::gl;

VertexArray::VertexArray() { GL_CALL(glGenVertexArrays(1, &m_vao)); }

VertexArray::~VertexArray() {}

void VertexArray::bind() const { GL_CALL(glBindVertexArray(m_vao)); }

void VertexArray::unbind() { GL_CALL(glBindVertexArray(0)); }

void VertexArray::add_buffer(const Buffer &vb, const VertexBufferLayout &layout,
                             bool instanced) {
  this->bind();
  vb.bind(gl::ARRAY_BUFFER);
  const auto &elements = layout.get_elements();
  unsigned long int offset = 0;

  for (unsigned int i = 0; i < elements.size(); i++) {
    GL_CALL(glVertexAttribPointer(elements[i].position, elements[i].count,
                                  elements[i].type, elements[i].normalized,
                                  layout.get_stride(), (const void *)offset));
    GL_CALL(glEnableVertexAttribArray(elements[i].position));

    if (instanced) {
      GL_CALL(glVertexAttribDivisor(elements[i].position, 1));
    }

    offset +=
        elements[i].count * VertexElement::get_size_of_type(elements[i].type);
  }
}

void VertexArray::destroy() { GL_CALL(glDeleteVertexArrays(1, &m_vao)); }
