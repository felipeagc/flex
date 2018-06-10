#pragma once

#include "drawable.hpp"
#include "mesh.hpp"

namespace flex {
class InstancedMesh : public Mesh, public InstancedDrawable {
public:
  InstancedMesh(
      std::vector<Vertex> vertices, std::vector<unsigned int> indices,
      std::vector<glm::mat4> transforms,
      std::vector<std::shared_ptr<gl::Texture>> diffuse_textures = {},
      std::vector<std::shared_ptr<gl::Texture>> specular_textures = {},
      std::vector<std::shared_ptr<gl::Texture>> normal_textures = {},
      std::vector<std::shared_ptr<gl::Texture>> height_textures = {});
  InstancedMesh(const Mesh &mesh, std::vector<glm::mat4> transforms);
  virtual ~InstancedMesh();

  void set_transforms(const std::vector<glm::mat4> transforms);

protected:
  void draw_instanced(GraphicsSystem &graphics) override;

private:
  gl::Buffer m_vb_instanced;
  std::vector<glm::mat4> m_transforms;
};
} // namespace flex
