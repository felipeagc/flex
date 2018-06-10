#pragma once

#include "gl.hpp"

namespace flex {
namespace gl {
class Framebuffer {
public:
  Framebuffer();
  virtual ~Framebuffer();

  void destroy();

  void bind() const;
  void unbind() const;

  // Checks if the currently bound framebuffer is complete
  static bool is_complete();

private:
  GLuint m_id;
};
} // namespace gl
} // namespace flex
