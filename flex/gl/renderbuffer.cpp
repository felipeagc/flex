#include "renderbuffer.hpp"

using namespace flex::gl;

Renderbuffer::Renderbuffer() { GL_CALL(glGenRenderbuffers(1, &m_id)); }

Renderbuffer::~Renderbuffer() { GL_CALL(glDeleteRenderbuffers(1, &m_id)); }

void Renderbuffer::bind() const {
  GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_id));
}

void Renderbuffer::unbind() const {
  GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

GLuint Renderbuffer::get_id() const { return m_id; }
