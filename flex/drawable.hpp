#pragma once

#include "gl/shader.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace flex {
class Drawable {
public:
  virtual ~Drawable(){};

  virtual void draw(gl::Shader &shader, glm::vec3 pos = glm::vec3(0.0),
                    glm::vec3 rot = glm::vec3(0.0),
                    glm::vec3 scale = glm::vec3(1.0)) = 0;
};

class InstancedDrawable {
public:
  virtual ~InstancedDrawable(){};

  virtual void draw_instanced(gl::Shader &shader) = 0;
};

} // namespace flex
