#pragma once

#include "drawable.hpp"

namespace flex {
class Model : public Drawable {
public:
  virtual ~Model(){};

protected:
  virtual void draw(GraphicsSystem &graphics, glm::vec3 pos = glm::vec3(0.0),
                    glm::vec3 rot = glm::vec3(0.0),
                    glm::vec3 scale = glm::vec3(1.0)) override = 0;
};
} // namespace flex
