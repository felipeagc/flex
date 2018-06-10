#include "buffer.hpp"

using namespace flex::gl;

Buffer::Buffer() { GL_CALL(glGenBuffers(1, &m_buffer)); }

Buffer::~Buffer() {}

void Buffer::buffer(BindTarget target, const void *data, const GLuint size) {
  this->bind(target);
  GL_CALL(glBufferData(target, size, data, GL_STATIC_DRAW));
}

void Buffer::buffer_sub_data(BindTarget target, const void *data,
                             const GLuint size, const GLintptr offset) {
  this->bind(target);
  GL_CALL(glBufferSubData(target, offset, size, data));
}

void Buffer::bind(BindTarget target) const {
  GL_CALL(glBindBuffer(target, m_buffer));
}

void Buffer::unbind(BindTarget target) { GL_CALL(glBindBuffer(target, 0)); }

void Buffer::destroy() { GL_CALL(glDeleteBuffers(1, &m_buffer)); }
