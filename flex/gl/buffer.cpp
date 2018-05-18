#include "buffer.hpp"

using namespace flex::gl;

Buffer::Buffer() { GL_CALL(glGenBuffers(1, &m_buffer)); }

Buffer::~Buffer() { GL_CALL(glDeleteBuffers(1, &m_buffer)); }
