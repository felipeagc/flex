#include "canvas.hpp"

using namespace flex;

const std::vector<Vertex> Canvas::VERTICES = {
    {{0.5f, 0.5f, .0f}, {}, {1.0, 1.0}},   // top right
    {{0.5f, -0.5f, .0f}, {}, {1.0, 0.0}},  // bottom right
    {{-0.5f, -0.5f, .0f}, {}, {0.0, 0.0}}, // bottom left
    {{-0.5f, 0.5f, .0f}, {}, {0.0, 1.0}},  // top left
};

const std::vector<u32> Canvas::INDICES{
    0, 1, 3, // first triangle
    1, 2, 3, // second triangle
};

Canvas::Canvas(u32 width, u32 height)
    : m_width(width), m_height(height) {
  create();
}

void Canvas::create() {
  m_fb.bind();

  // Get the texture ready
  m_texture.bind();

  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
                       GL_UNSIGNED_BYTE, NULL));

  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  m_texture.unbind();

  // Link texture to framebuffer
  GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                 GL_TEXTURE_2D, m_texture.get_id(), 0));

  // Get the renderbuffer ready
  m_rb.bind();
  GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width,
                                m_height));
  m_rb.unbind();

  // Link renderbuffer to the framebuffer
  GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                    GL_RENDERBUFFER, m_rb.get_id()));

  m_rb.unbind();
  m_texture.unbind();

  if (!gl::Framebuffer::is_complete()) {
    flex::log(L_ERROR, L_RENDER, "Framebuffer is not complete!");
  }

  m_fb.unbind();
}

Canvas::~Canvas() {
  m_texture.destroy();
  m_rb.destroy();
  m_fb.destroy();
}

void Canvas::bind() const {
  m_fb.bind();
  GL_CALL(glViewport(0, 0, m_width, m_height));
}

void Canvas::unbind(Window &window) const {
  m_fb.unbind();
  GL_CALL(glViewport(0, 0, window.get_width(), window.get_height()));
}

void Canvas::draw(gl::Shader &shader, glm::vec3 pos, glm::vec3 rot,
                  glm::vec3 scale) {
  m_texture.bind();
  m_mesh.draw(shader, pos, rot,
              {m_width * scale.x, m_height * scale.y, scale.z});
  m_texture.unbind();
}

u32 Canvas::get_width() const { return m_width; }

u32 Canvas::get_height() const { return m_height; }

void Canvas::resize(u32 width, u32 height) {
  m_texture.destroy();
  m_rb.destroy();
  m_fb.destroy();

  m_width = width;
  m_height = height;

  m_fb = gl::Framebuffer{};
  m_rb = gl::Renderbuffer{};
  m_texture = gl::Texture{};

  create();
}
