#include "graphics.hpp"

using namespace flex;

GraphicsSystem::GraphicsSystem() {}

GraphicsSystem::~GraphicsSystem() {}

void GraphicsSystem::use_shader(gl::Shader &shader) {
  m_current_shader = &shader;
  shader.use();
}

gl::Shader *GraphicsSystem::get_shader() const { return m_current_shader; }

void GraphicsSystem::draw(Drawable &drawable, glm::vec3 pos, glm::vec3 rot,
                          glm::vec3 scale) {
  drawable.draw(*this, pos, rot, scale);
}

void GraphicsSystem::draw_instanced(InstancedDrawable &drawable) {
  drawable.draw_instanced(*this);
}
