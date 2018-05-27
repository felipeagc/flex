#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace flex {
class GraphicsSystem;
class Drawable {
  friend class GraphicsSystem;

public:
  virtual ~Drawable(){};

protected:
  virtual void draw(GraphicsSystem &graphics, glm::vec3 pos = glm::vec3(0.0),
                    glm::vec3 rot = glm::vec3(0.0),
                    glm::vec3 scale = glm::vec3(1.0)) = 0;
};

class InstancedDrawable {
  friend class GraphicsSystem;

public:
  virtual ~InstancedDrawable(){};

protected:
  virtual void draw_instanced(GraphicsSystem &graphics) = 0;
};

} // namespace flex
