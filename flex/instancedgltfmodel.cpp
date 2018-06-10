#include "instancedgltfmodel.hpp"
#include "graphics.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace flex;

InstancedGltfModel::InstancedGltfModel(const std::string &path,
                                       std::vector<glm::mat4> transforms)
    : GltfModel(path) {
  m_transforms = transforms;
  m_vb_instanced.buffer(gl::ARRAY_BUFFER, transforms.data(),
                        transforms.size() * sizeof(glm::mat4));

  flex::gl::VertexBufferLayout layout;
  int pos = 3;
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4

  for (auto &mpair : m_meshes) {
    auto &mesh = mpair.second;
    for (auto &ppair : mesh.primitives) {
      auto &prim = ppair.second;

      prim.va.add_buffer(m_vb_instanced, layout, true);
    }
  }
}

InstancedGltfModel::InstancedGltfModel(const GltfModel &model,
                                       std::vector<glm::mat4> transforms)
    : GltfModel(model) {
  m_transforms = transforms;
  m_vb_instanced.buffer(gl::ARRAY_BUFFER, transforms.data(),
                        transforms.size() * sizeof(glm::mat4));

  flex::gl::VertexBufferLayout layout;
  int pos = 3;
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4
  layout.push_float(4, pos++); // vec4

  for (auto &mpair : m_meshes) {
    auto &mesh = mpair.second;
    for (auto &ppair : mesh.primitives) {
      auto &prim = ppair.second;

      prim.va.add_buffer(m_vb_instanced, layout, true);
    }
  }
}

InstancedGltfModel::~InstancedGltfModel() { m_vb_instanced.destroy(); }

void InstancedGltfModel::set_transforms(
    const std::vector<glm::mat4> transforms) {
  m_transforms = transforms;
  m_vb_instanced.buffer(gl::ARRAY_BUFFER, transforms.data(),
                        transforms.size() * sizeof(glm::mat4));
}

void InstancedGltfModel::draw_instanced(GraphicsSystem &graphics) {
  auto shader = graphics.get_shader(flex::SHADER_INSTANCED);

  auto model = glm::mat4(1.0f);
  for (auto &node : m_nodes) {
    draw_node_instanced(node, model, shader);
  }
}

void InstancedGltfModel::draw_node_instanced(GltfNode &node, glm::mat4 &model,
                                             gl::Shader *shader) {
  auto node_model = model * node.transform;

  if (node.mesh != -1) {
    auto &mesh = m_meshes[node.mesh];

    for (auto &ppair : mesh.primitives) {
      const auto &prim = ppair.second;

      if (prim.diffuse_texture_index != -1) {
        auto &texture = m_textures[prim.diffuse_texture_index];
        texture.bind(0);
        shader->set("texture_diffuse0", (unsigned int)0);

        shader->set("is_textured", true);
      } else {
        shader->set("is_textured", false);
      }

      shader->set("model", node_model);

      if (prim.index_buffer_index != -1) {
        prim.va.bind();
        gl::Buffer &ib = m_buffers[prim.index_buffer_index];
        ib.bind(gl::ELEMENT_ARRAY_BUFFER);
        GL_CALL(glDrawElementsInstanced(prim.mode, prim.index_count,
                                        prim.index_type, 0,
                                        m_transforms.size()));
      } else {
        prim.va.bind();
        GL_CALL(glDrawArraysInstanced(prim.mode, 0, prim.vertex_count,
                                      m_transforms.size()));
      }
    }
  }

  for (auto &child : node.children) {
    draw_node_instanced(child, node_model, shader);
  }
}
