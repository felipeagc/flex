#pragma once

#include "gl/shader.hpp"
#include <glm/glm.hpp>

namespace flex {
class Drawable {
public:
  virtual ~Drawable(){};

  virtual void draw(gl::Shader &shader, glm::vec3 pos = glm::vec3(0.0),
                    glm::vec3 rot = glm::vec3(0.0),
                    glm::vec3 scale = glm::vec3(1.0)) = 0;
};

class Drawable2D {
public:
  virtual ~Drawable2D(){};

  virtual void draw(gl::Shader &shader, glm::vec2 pos = glm::vec2(0.0),
                    float rotation = 0.0f,
                    glm::vec2 scale = glm::vec2(1.0)) = 0;
};

class InstancedDrawable {
public:
  virtual ~InstancedDrawable(){};

  virtual void draw_instanced(gl::Shader &shader) = 0;
};

} // namespace flex
