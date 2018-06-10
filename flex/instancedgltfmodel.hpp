#pragma once

#include "gl/buffer.hpp"
#include "gltfmodel.hpp"

namespace flex {
class InstancedGltfModel : public GltfModel, public InstancedDrawable {
public:
  InstancedGltfModel(const std::string &path,
                     std::vector<glm::mat4> transforms);
  InstancedGltfModel(const GltfModel &model, std::vector<glm::mat4> transforms);
  ~InstancedGltfModel();

  void set_transforms(const std::vector<glm::mat4> transforms);

  void draw_instanced(gl::Shader &shader) override;

protected:

  void draw_node_instanced(GltfNode &node, glm::mat4 &model,
                           gl::Shader &shader);

private:
  gl::Buffer m_vb_instanced;
  std::vector<glm::mat4> m_transforms;
};
} // namespace flex
