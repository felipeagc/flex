#pragma once

#include <flex/gl/framebuffer.hpp>
#include <flex/gl/renderbuffer.hpp>
#include <flex/gl/texture.hpp>

namespace flex {
class Canvas {
public:
  Canvas(unsigned int width, unsigned int height);
  ~Canvas();

  void bind() const;
  void unbind() const;

private:
  gl::Texture m_texture;
  gl::Renderbuffer m_rb;
  gl::Framebuffer m_fb;
};
} // namespace flex
