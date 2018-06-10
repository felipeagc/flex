#include "sprite.hpp"

using namespace flex;

const std::vector<Vertex> Sprite::VERTICES = {
    {{0.5f, 0.5f, .0f}, {}, {1.0, 1.0}},   // top right
    {{0.5f, -0.5f, .0f}, {}, {1.0, 0.0}},  // bottom right
    {{-0.5f, -0.5f, .0f}, {}, {0.0, 0.0}}, // bottom left
    {{-0.5f, 0.5f, .0f}, {}, {0.0, 1.0}},  // top left
};

const std::vector<unsigned int> Sprite::INDICES{
    0, 1, 3, // first triangle
    1, 2, 3, // second triangle
};

Sprite::Sprite(const std::string &path, gl::TextureFilter filter) {
  m_texture.load_from_file(path);
  m_texture.set_min_filter(filter);
  m_texture.set_mag_filter(filter);

  m_mesh.add_diffuse_texture(m_texture);
}

Sprite::~Sprite() { m_texture.destroy(); }

void Sprite::draw(gl::Shader &shader, glm::vec2 pos, float rotation,
                  glm::vec2 scale) {
  m_mesh.draw(
      shader, {pos.x, pos.y, 0.0}, {0.0, 0.0, rotation},
      {scale.x * m_texture.get_width(), scale.y * m_texture.get_height(), 1.0});
}
