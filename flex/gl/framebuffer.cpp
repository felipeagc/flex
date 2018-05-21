#include <flex/gl/framebuffer.hpp>

using namespace flex::gl;

Framebuffer::Framebuffer() { GL_CALL(glGenFramebuffers(1, &m_id)); }

Framebuffer::~Framebuffer() { GL_CALL(glDeleteFramebuffers(1, &m_id)); }

void Framebuffer::bind() const {
  GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
}

void Framebuffer::unbind() const {
  GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

bool Framebuffer::is_complete() {
  GL_CALL(auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER));
  return (status == GL_FRAMEBUFFER_COMPLETE);
}
