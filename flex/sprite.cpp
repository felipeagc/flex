#include "sprite.hpp"

using namespace flex;

const std::vector<Vertex> Sprite::VERTICES = {
    {{1.0f, 1.0f, .0f}, {}, {1.0, 0.0}},   // top right
    {{1.0f, -1.0f, .0f}, {}, {1.0, 1.0}},  // bottom right
    {{-1.0f, -1.0f, .0f}, {}, {0.0, 1.0}}, // bottom left
    {{-1.0f, 1.0f, .0f}, {}, {0.0, 0.0}},  // top left
};

const std::vector<unsigned int> Sprite::INDICES{
    0, 1, 3, // first triangle
    1, 2, 3, // second triangle
};

Sprite::Sprite(const std::string &path, gl::TextureFilter filter) {
  m_texture = std::make_shared<gl::Texture>(filter);
  m_texture->load_from_file(path);

  m_mesh.add_diffuse_texture(m_texture);
}

Sprite::Sprite(std::shared_ptr<gl::Texture> texture) {
  m_texture = texture;

  m_mesh.add_diffuse_texture(m_texture);
}

Sprite::~Sprite() {}

void Sprite::draw(GraphicsSystem &graphics, glm::vec3 pos, glm::vec3 rot,
                  glm::vec3 scale) {
  graphics.draw(m_mesh, pos, rot, scale);
}
