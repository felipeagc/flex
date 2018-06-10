#include "graphics.hpp"

using namespace flex;

GraphicsSystem::GraphicsSystem() {}

GraphicsSystem::~GraphicsSystem() {}

void GraphicsSystem::push_shader(gl::Shader &shader) {
  m_shader_stack.push(&shader);
}

void GraphicsSystem::pop_shader() { m_shader_stack.pop(); }

gl::Shader *GraphicsSystem::get_shader(ShaderType type) {
  if (m_shader_stack.size() > 0) {
    return m_shader_stack.top();
  }

  if (type == SHADER_INSTANCED) {
    return &m_shader_default_instanced;
  }

  return &m_shader_default;
}

gl::Shader *GraphicsSystem::get_shader_default() { return &m_shader_default; }

gl::Shader *GraphicsSystem::get_shader_default_instanced() {
  return &m_shader_default_instanced;
}

void GraphicsSystem::draw(Drawable &drawable, glm::vec3 pos, glm::vec3 rot,
                          glm::vec3 scale) {
  drawable.draw(*this, pos, rot, scale);
}

void GraphicsSystem::draw_instanced(InstancedDrawable &drawable) {
  drawable.draw_instanced(*this);
}
