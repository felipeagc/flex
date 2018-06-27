#pragma once

#include <glm/glm.hpp>
#include "types.hpp"

namespace flex {
inline glm::vec3 lerp(glm::vec3 v1, glm::vec3 v2, f32 t) {
  return v1 + t * (v2 - v1);
}
} // namespace flex
