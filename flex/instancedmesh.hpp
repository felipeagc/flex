#pragma once

#include "drawable.hpp"
#include "mesh.hpp"

namespace flex {
class InstancedMesh : public Mesh, public InstancedDrawable {
public:
  InstancedMesh(
      std::vector<Vertex> vertices, std::vector<unsigned int> indices,
      std::vector<glm::mat4> transforms,
      std::vector<gl::Texture> diffuse_textures = {},
      std::vector<gl::Texture> specular_textures = {},
      std::vector<gl::Texture> normal_textures = {},
      std::vector<gl::Texture> height_textures = {});
  InstancedMesh(const Mesh &mesh, std::vector<glm::mat4> transforms);
  virtual ~InstancedMesh();

  void set_transforms(const std::vector<glm::mat4> transforms);

  void draw_instanced(gl::Shader &shader) override;

private:
  gl::Buffer m_vb_instanced;
  std::vector<glm::mat4> m_transforms;
};
} // namespace flex
