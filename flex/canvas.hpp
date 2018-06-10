#pragma once

#include "drawable.hpp"
#include "gl/framebuffer.hpp"
#include "gl/renderbuffer.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "graphics.hpp"
#include "mesh.hpp"
#include <memory>

namespace flex {
class Canvas : public Drawable {
public:
  Canvas(unsigned int width, unsigned int height);
  virtual ~Canvas();

  void bind() const;
  void unbind() const;

  unsigned int get_width() const;
  unsigned int get_height() const;

protected:
  void draw(GraphicsSystem &graphics, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0),
            glm::vec3 scale = glm::vec3(1.0)) override;


private:
  static const std::vector<Vertex> VERTICES;
  static const std::vector<unsigned int> INDICES;

  unsigned int m_width, m_height;

  gl::Texture m_texture;
  gl::Renderbuffer m_rb;
  gl::Framebuffer m_fb;
  Mesh m_mesh{VERTICES, INDICES, {m_texture}};
};
} // namespace flex
