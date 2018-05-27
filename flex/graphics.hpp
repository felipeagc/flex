#pragma once

#include "drawable.hpp"
#include "gl/shader.hpp"

namespace flex {

class GraphicsSystem {
private:
  gl::Shader *m_current_shader = nullptr;

public:
  GraphicsSystem();
  ~GraphicsSystem();

  void use_shader(gl::Shader &shader);

  // Returns the current shader
  gl::Shader *get_shader() const;

  void draw(Drawable &drawable, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0), glm::vec3 scale = glm::vec3(1.0));

  void draw_instanced(InstancedDrawable &drawable);
};
} // namespace flex
