#pragma once

#include "instancedmesh.hpp"
#include "model.hpp"

namespace flex {
class InstancedModel : public Model, public InstancedDrawable {
public:
  InstancedModel(const std::string &path, std::vector<glm::mat4> transforms);
  InstancedModel(const Model &model, std::vector<glm::mat4> transforms);
  ~InstancedModel();

  void set_transforms(const std::vector<glm::mat4> transforms);

protected:
  void draw_instanced(GraphicsSystem &graphics) override;
};
} // namespace flex
