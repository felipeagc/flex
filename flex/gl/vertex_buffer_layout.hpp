#pragma once

#include "gl.hpp"
#include <vector>

namespace flex {
namespace gl {

struct VertexElement {
  unsigned int position;
  GLuint type;
  unsigned int count;
  bool normalized;

  static unsigned int get_size_of_type(unsigned int type) {
    switch (type) {
    case GL_FLOAT:
      return sizeof(GLfloat);
    case GL_UNSIGNED_INT:
      return sizeof(GLuint);
    case GL_UNSIGNED_BYTE:
      return sizeof(GLubyte);
    }
    return 0;
  }
};

class VertexBufferLayout {
public:
  VertexBufferLayout() : m_stride(0){};
  ~VertexBufferLayout(){};

  void push_float(unsigned int count, unsigned int position) {
    m_elements.push_back({position, GL_FLOAT, count, false});
    m_stride += VertexElement::get_size_of_type(GL_FLOAT) * count;
  }

  void push_uint(unsigned int count, unsigned int position) {
    m_elements.push_back({position, GL_UNSIGNED_INT, count, false});
    m_stride += VertexElement::get_size_of_type(GL_UNSIGNED_INT) * count;
  }

  void push_ubyte(unsigned int count, unsigned int position) {
    m_elements.push_back({position, GL_UNSIGNED_BYTE, count, false});
    m_stride += VertexElement::get_size_of_type(GL_UNSIGNED_BYTE) * count;
  }

  inline unsigned int get_stride() const { return m_stride; };

  inline const std::vector<VertexElement> get_elements() const {
    return m_elements;
  }

private:
  unsigned int m_stride;
  std::vector<VertexElement> m_elements;
};

} // namespace gl
} // namespace flex
