#include "instancedmesh.hpp"

using namespace flex;

InstancedMesh::InstancedMesh(
    std::vector<Vertex> vertices, std::vector<unsigned int> indices,
    std::vector<glm::mat4> transforms,
    std::vector<std::shared_ptr<gl::Texture>> diffuse_textures,
    std::vector<std::shared_ptr<gl::Texture>> specular_textures,
    std::vector<std::shared_ptr<gl::Texture>> normal_textures,
    std::vector<std::shared_ptr<gl::Texture>> height_textures)
    : Mesh(vertices, indices, diffuse_textures, specular_textures,
           normal_textures, height_textures) {
  m_transforms = transforms;
  m_vb_instanced->buffer(transforms.data(),
                         transforms.size() * sizeof(glm::mat4));

  flex::gl::VertexBufferLayout layout;
  layout.push_float(4); // vec4
  layout.push_float(4); // vec4
  layout.push_float(4); // vec4
  layout.push_float(4); // vec4

  m_va->add_buffer(*m_vb_instanced, layout, true);
}

InstancedMesh::InstancedMesh(const Mesh &mesh,
                             std::vector<glm::mat4> transforms)
    : Mesh(mesh) {
  m_transforms = transforms;
  m_vb_instanced->buffer(transforms.data(),
                         transforms.size() * sizeof(glm::mat4));

  flex::gl::VertexBufferLayout layout;
  layout.push_float(4); // vec4
  layout.push_float(4); // vec4
  layout.push_float(4); // vec4
  layout.push_float(4); // vec4

  m_va->add_buffer(*m_vb_instanced, layout, true);
}

InstancedMesh::~InstancedMesh() {}

void InstancedMesh::set_transforms(const std::vector<glm::mat4> transforms) {
  m_transforms = transforms;
  m_vb_instanced->buffer(transforms.data(),
                         transforms.size() * sizeof(glm::mat4));
}

void InstancedMesh::draw_instanced(GraphicsSystem &graphics) {
  auto shader = graphics.get_shader();
  if (shader == nullptr) {
    flex::log(L_ERROR, L_RENDER,
              "Couldn't draw mesh: no shader currently bound");
    return;
  }

  this->bind_textures(*shader);

  m_va->bind();
  m_ib->bind();
  gl::draw_elements_instanced(m_indices.size(), m_transforms.size());
}
