#pragma once

#include "drawable.hpp"
#include "gl/framebuffer.hpp"
#include "gl/renderbuffer.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "mesh.hpp"
#include "window.hpp"

namespace flex {
class Canvas : public Drawable {
public:
  Canvas(u32 width, u32 height);
  virtual ~Canvas();

  void bind() const;
  void unbind(Window &window) const;

  void resize(u32 width, u32 height);

  u32 get_width() const;
  u32 get_height() const;

  void draw(gl::Shader &shader, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0),
            glm::vec3 scale = glm::vec3(1.0)) override;

private:
  static const std::vector<Vertex> VERTICES;
  static const std::vector<u32> INDICES;

  void create();

  u32 m_width, m_height;

  gl::Texture m_texture;
  gl::Renderbuffer m_rb;
  gl::Framebuffer m_fb;
  Mesh m_mesh{VERTICES, INDICES, {m_texture}};
};
} // namespace flex
