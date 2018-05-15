#pragma once

#include <glad/glad.h>
#include <vector>

namespace flex {
namespace gl {

struct VertexElement {
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

  void push_element(VertexElement element) { m_elements.push_back(element); }

  inline unsigned int get_stride() const { return m_stride; };
  void add_to_stride(unsigned int val) { m_stride += val; }

  inline const std::vector<VertexElement> get_elements() const {
    return m_elements;
  }

private:
  unsigned int m_stride;
  std::vector<VertexElement> m_elements;
};

template <typename T>
void push_element(VertexBufferLayout &layout, unsigned int count) {}

template <> void push_element<float>(VertexBufferLayout &layout, unsigned int count) {
  layout.push_element({GL_FLOAT, count, false});
  layout.add_to_stride(VertexElement::get_size_of_type(GL_FLOAT) * count);
}

template <>
void push_element<unsigned int>(VertexBufferLayout &layout, unsigned int count) {
  layout.push_element({GL_UNSIGNED_INT, count, false});
  layout.add_to_stride(VertexElement::get_size_of_type(GL_UNSIGNED_INT) *
                       count);
}

template <>
void push_element<unsigned char>(VertexBufferLayout &layout, unsigned int count) {
  layout.push_element({GL_UNSIGNED_BYTE, count, false});
  layout.add_to_stride(VertexElement::get_size_of_type(GL_UNSIGNED_BYTE) *
                       count);
}

} // namespace gl
} // namespace flex
