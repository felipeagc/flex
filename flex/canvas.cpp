#include "canvas.hpp"

using namespace flex;

const std::vector<Vertex> Canvas::VERTICES = {
    {{1.0f, 1.0f, .0f}, {}, {1.0, 1.0}},   // top right
    {{1.0f, -1.0f, .0f}, {}, {1.0, 0.0}},  // bottom right
    {{-1.0f, -1.0f, .0f}, {}, {0.0, 0.0}}, // bottom left
    {{-1.0f, 1.0f, .0f}, {}, {0.0, 1.0}},  // top left
};

const std::vector<unsigned int> Canvas::INDICES{
    0, 1, 3, // first triangle
    1, 2, 3, // second triangle
};

Canvas::Canvas(unsigned int width, unsigned int height)
    : m_width(width), m_height(height) {
  m_fb.bind();

  // Get the texture ready
  m_texture->bind();

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
                                 GL_TEXTURE_2D, m_texture->get_id(), 0));
  GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                    GL_RENDERBUFFER, m_rb.get_id()));

  m_rb.unbind();
  m_texture->unbind();

  if (!gl::Framebuffer::is_complete()) {
    flex::log(L_ERROR, L_RENDER, "Framebuffer is not complete!");
  }

  m_fb.unbind();
}

Canvas::~Canvas() {}

void Canvas::bind() const { m_fb.bind(); }

void Canvas::unbind() const { m_fb.unbind(); }

void Canvas::draw(GraphicsSystem &graphics, glm::vec3 pos, glm::vec3 rot,
                  glm::vec3 scale) {
  graphics.draw(m_mesh, pos, rot, scale);
}

unsigned int Canvas::get_width() const { return m_width; }

unsigned int Canvas::get_height() const { return m_height; }
