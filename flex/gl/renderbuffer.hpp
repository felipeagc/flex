#pragma once

#include "gl.hpp"

namespace flex {
namespace gl {
class Renderbuffer {
public:
  Renderbuffer();
  virtual ~Renderbuffer();

  void destroy();

  void bind() const;
  void unbind() const;

  GLuint get_id() const;

private:
  GLuint m_id;
};
} // namespace gl
} // namespace flex
