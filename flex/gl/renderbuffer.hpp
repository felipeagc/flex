#pragma once

#include <glad/glad.h>
#include <flex/gl/util.hpp>

namespace flex {
namespace gl {
class Renderbuffer {
public:
  Renderbuffer();
  ~Renderbuffer();

  void bind() const;
  void unbind() const;

  GLuint get_id() const;

private:
  GLuint m_id;
};
} // namespace gl
} // namespace flex
