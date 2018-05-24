#include "canvas.hpp"

using namespace flex;

Canvas::Canvas(unsigned int width, unsigned int height) {
  m_fb.bind();

  // Get the texture ready
  m_texture.bind();

  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                       GL_UNSIGNED_BYTE, NULL));

  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  // Get the renderbuffer ready
  m_rb.bind();

  GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width,
                                height));

  // Link them to the framebuffer
  GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                 GL_TEXTURE_2D, m_texture.get_id(), 0));
  GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                    GL_RENDERBUFFER, m_rb.get_id()));

  m_rb.unbind();
  m_texture.unbind();

  if (!gl::Framebuffer::is_complete()) {
    flex::log(L_ERROR, L_RENDER, "ERROR: Framebuffer is not complete!");
  }

  m_fb.unbind();
}

Canvas::~Canvas() {}

void Canvas::bind() const {
  m_fb.bind();
}

void Canvas::unbind() const {
  m_fb.unbind();
}
