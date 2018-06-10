#include "instancedmesh.hpp"

using namespace flex;

InstancedMesh::InstancedMesh(std::vector<Vertex> vertices,
                             std::vector<unsigned int> indices,
                             std::vector<glm::mat4> transforms,
                             std::vector<gl::Texture> diffuse_textures,
                             std::vector<gl::Texture> specular_textures,
                             std::vector<gl::Texture> normal_textures,
                             std::vector<gl::Texture> height_textures)
    : Mesh(vertices, indices, diffuse_textures, specular_textures,
           normal_textures, height_textures) {
  m_transforms = transforms;
  m_vb_instanced.buffer(gl::ARRAY_BUFFER, transforms.data(),
                        transforms.size() * sizeof(glm::mat4));

  flex::gl::VertexBufferLayout layout;
  int pos = 3;
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4

  m_va.add_buffer(m_vb_instanced, layout, true);
}

InstancedMesh::InstancedMesh(const Mesh &mesh,
                             std::vector<glm::mat4> transforms)
    : Mesh(mesh) {
  m_transforms = transforms;
  m_vb_instanced.buffer(gl::ARRAY_BUFFER, transforms.data(),
                        transforms.size() * sizeof(glm::mat4));

  flex::gl::VertexBufferLayout layout;
  int pos = 3;
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4

  m_va.add_buffer(m_vb_instanced, layout, true);
}

InstancedMesh::~InstancedMesh() { m_vb_instanced.destroy(); }

void InstancedMesh::set_transforms(const std::vector<glm::mat4> transforms) {
  m_transforms = transforms;
  m_vb_instanced.buffer(gl::ARRAY_BUFFER, transforms.data(),
                        transforms.size() * sizeof(glm::mat4));
}

void InstancedMesh::draw_instanced(GraphicsSystem &graphics) {
  auto shader = graphics.get_shader(flex::SHADER_INSTANCED);

  this->bind_textures(*shader);

  shader->set("model", glm::mat4(1.0f));

  m_va.bind();
  m_ib.bind(gl::ELEMENT_ARRAY_BUFFER);
  gl::draw_elements_instanced(m_indices.size(), m_transforms.size());
}
