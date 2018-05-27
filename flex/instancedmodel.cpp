#include "instancedmodel.hpp"

using namespace flex;

InstancedModel::InstancedModel(const std::string &path,
                               std::vector<glm::mat4> transforms)
    : Model(path) {
  for (auto &mesh : m_meshes) {
    mesh = std::make_shared<InstancedMesh>(*mesh, transforms);
  }
}

InstancedModel::InstancedModel(const Model &model,
                               std::vector<glm::mat4> transforms)
    : Model(model) {
  for (auto &mesh : m_meshes) {
    mesh = std::make_shared<InstancedMesh>(*mesh, transforms);
  }
}

InstancedModel::~InstancedModel() {}

void InstancedModel::set_transforms(const std::vector<glm::mat4> transforms) {
  for (auto &mesh : m_meshes) {
    InstancedMesh *imesh = static_cast<InstancedMesh *>(mesh.get());
    imesh->set_transforms(transforms);
  }
}

void InstancedModel::draw_instanced(GraphicsSystem &graphics) {
  for (auto &mesh : m_meshes) {
    graphics.draw_instanced(*static_cast<InstancedMesh *>(mesh.get()));
  }
}
