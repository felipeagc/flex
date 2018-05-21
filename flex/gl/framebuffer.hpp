#pragma once

#include <flex/gl/util.hpp>
#include <glad/glad.h>

namespace flex {
namespace gl {
class Framebuffer {
public:
  Framebuffer();
  ~Framebuffer();

  void bind() const;
  void unbind() const;

  // Checks if the currently bound framebuffer is complete
  static bool is_complete();

private:
  GLuint m_id;
};
} // namespace gl
} // namespace flex
