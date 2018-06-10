#pragma once

#include "drawable.hpp"
#include "gl/texture.hpp"
#include "mesh.hpp"
#include <memory>

namespace flex {
class Sprite : public Drawable2D {
private:
  static const std::vector<Vertex> VERTICES;
  static const std::vector<unsigned int> INDICES;

  Mesh m_mesh{VERTICES, INDICES};
  gl::Texture m_texture;

public:
  Sprite(const std::string &path, gl::TextureFilter filter = gl::FILTER_LINEAR);
  ~Sprite();

  void draw(gl::Shader &shader, glm::vec2 pos = glm::vec2(0.0),
            float rotation = 0.0, glm::vec2 scale = glm::vec2(1.0)) override;
};
} // namespace flex
