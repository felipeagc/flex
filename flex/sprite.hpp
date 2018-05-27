#pragma once

#include "drawable.hpp"
#include "gl/texture.hpp"
#include "mesh.hpp"
#include <memory>

namespace flex {
class Sprite : public Drawable {
private:
  static const std::vector<Vertex> VERTICES;
  static const std::vector<unsigned int> INDICES;

  Mesh m_mesh{VERTICES, INDICES};
  std::shared_ptr<gl::Texture> m_texture;

public:
  Sprite(const std::string &path, gl::TextureFilter filter = gl::FILTER_LINEAR);
  Sprite(std::shared_ptr<gl::Texture> texture);
  ~Sprite();

protected:
  void draw(GraphicsSystem &graphics, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0),
            glm::vec3 scale = glm::vec3(1.0)) override;
};
} // namespace flex
