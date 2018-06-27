#include "gltfmodel.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <tiny_gltf.h>

using namespace flex;

GltfNode process_node(const tinygltf::Model &model,
                      const tinygltf::Node &node) {
  GltfNode gltf_node;

  gltf_node.mesh = node.mesh;

  if (node.matrix.size() == 16) {
    // Has matrix
    gltf_node.transform = glm::mat4{
        node.matrix[0],  node.matrix[1],  node.matrix[2],  node.matrix[3],
        node.matrix[4],  node.matrix[5],  node.matrix[6],  node.matrix[7],
        node.matrix[8],  node.matrix[9],  node.matrix[10], node.matrix[11],
        node.matrix[12], node.matrix[13], node.matrix[14], node.matrix[15],
    };
  } else {
    // Individual transformations
    glm::vec3 translation(0, 0, 0);
    glm::quat rotation(1, 0, 0, 0);
    glm::vec3 scale(1, 1, 1);

    if (node.translation.size() == 3) {
      translation = glm::vec3(node.translation[0], node.translation[1],
                              node.translation[2]);
    }

    if (node.rotation.size() == 4) {
      auto x = node.rotation[0];
      auto y = node.rotation[1];
      auto z = node.rotation[2];
      auto w = node.rotation[3];
      rotation = glm::quat(w, x, y, z);
    }

    if (node.scale.size() == 3) {
      scale = glm::vec3(node.scale[0], node.scale[1], node.scale[2]);
    }

    auto node_translation = glm::translate(glm::mat4(1.0f), translation);
    auto node_rotation = glm::toMat4(rotation);
    auto node_scaling = glm::scale(glm::mat4(1.0f), scale);

    gltf_node.transform = node_translation * node_rotation * node_scaling;
  }

  for (size_t i = 0; i < node.children.size(); i++) {
    gltf_node.children.push_back(
        process_node(model, model.nodes[node.children[i]]));
  }

  return gltf_node;
}

GltfModel::GltfModel(const std::string &path) {
  tinygltf::Model model;
  tinygltf::TinyGLTF loader;
  std::string err;
  bool ret;

  std::string ext = path.substr(path.find_last_of('.'), path.size());
  if (ext == ".glb") {
    ret = loader.LoadBinaryFromFile(&model, &err, path);
  } else {
    ret = loader.LoadASCIIFromFile(&model, &err, path);
  }

  if (!err.empty()) {
    flex::log(L_ERROR, L_IMPORT, err.c_str());
    return;
  }

  if (!ret) {
    flex::log(L_ERROR, L_IMPORT, "Failed to parse glTF: '%s'", path.c_str());
    return;
  }

  for (size_t i = 0; i < model.bufferViews.size(); i++) {
    const auto &buffer_view = model.bufferViews[i];
    const auto &buffer = model.buffers[buffer_view.buffer];

    u32 target = GL_ARRAY_BUFFER;
    if (buffer_view.target != 0)
      target = buffer_view.target;

    std::vector<unsigned char> data{
        &buffer.data[buffer_view.byteOffset],
        &buffer.data[buffer_view.byteOffset + buffer_view.byteLength]};

    m_buffers[i] = gl::Buffer{};

    m_buffers[i].buffer((gl::BindTarget)target, data.data(),
                        buffer_view.byteLength);
  }

  for (size_t i = 0; i < model.textures.size(); i++) {
    tinygltf::Texture tex = model.textures[0];
    tinygltf::Image img = model.images[tex.source];
    GLenum format = GL_RGBA;
    if (img.component == 3) {
      format = GL_RGB;
    }

    m_textures[i] = {};
    gl::Texture &texture = m_textures[i];

    texture.load_from_data(&img.image.at(0), img.width, img.height, format);
    if (tex.sampler != -1) {
      texture.set_min_filter(
          (gl::TextureFilter)model.samplers[tex.sampler].minFilter);
      texture.set_mag_filter(
          (gl::TextureFilter)model.samplers[tex.sampler].magFilter);
    } else {
      texture.set_min_filter(gl::FILTER_LINEAR);
      texture.set_mag_filter(gl::FILTER_LINEAR);
    }
  }

  for (size_t i = 0; i < model.meshes.size(); i++) {
    const auto &mesh = model.meshes[i];

    m_meshes[i] = {};
    GltfMesh &gltf_mesh = m_meshes[i];

    for (size_t j = 0; j < mesh.primitives.size(); j++) {
      const auto &prim = mesh.primitives[j];

      gltf_mesh.primitives[j] = {};
      GltfPrimitive &primitive = gltf_mesh.primitives[j];

      if (prim.indices != -1) {
        primitive.index_buffer_index = model.accessors[prim.indices].bufferView;
      }

      const auto &indices_accessor = model.accessors[prim.indices];
      primitive.index_count = indices_accessor.count;
      primitive.index_type = indices_accessor.componentType;

      primitive.mode = prim.mode;

      primitive.diffuse_texture_index = -1;
      if (prim.material != -1) {
        auto &material = model.materials[prim.material];

        if (material.values.count("baseColorTexture")) {
          auto &tex_val = material.values["baseColorTexture"];
          primitive.diffuse_texture_index =
              (i32)tex_val.json_double_value["index"];
        }
      }

      primitive.va.bind();

      for (auto &pair : prim.attributes) {
        const auto &attr_name = pair.first;
        const auto &accessor = model.accessors[pair.second];

        // Initialize vertex count
        primitive.vertex_count = accessor.count;

        if (m_buffers.count(accessor.bufferView)) {
          const auto &buffer = m_buffers[accessor.bufferView];

          flex::gl::VertexBufferLayout layout;

          if (attr_name == "POSITION") {
            layout.push_float(3, 0); // position
          } else if (attr_name == "NORMAL") {
            layout.push_float(3, 1); // normal
          } else if (attr_name == "TEXCOORD_0") {
            layout.push_float(2, 2); // tex_coords
          }

          primitive.va.add_buffer(buffer, layout);
        }
      }
    }
  }

  auto scene = model.scenes[0];

  for (size_t i = 0; i < scene.nodes.size(); i++) {
    const auto &node = model.nodes[scene.nodes[i]];

    GltfNode gltf_node = process_node(model, node);

    m_nodes.push_back(gltf_node);
  }
}

GltfModel::~GltfModel() {
  for (auto &mpair : m_meshes) {
    auto &mesh = mpair.second;
    for (auto &ppair : mesh.primitives) {
      auto &prim = ppair.second;
      prim.va.destroy();
    }
  }

  for (auto &bpair : m_buffers) {
    auto &buffer = bpair.second;
    buffer.destroy();
  }

  for (auto &tpair : m_textures) {
    auto &texture = tpair.second;
    texture.destroy();
  }
}

void GltfModel::draw(gl::Shader &shader, glm::vec3 pos, glm::vec3 rot,
                     glm::vec3 scale) {

  auto translation = glm::translate(glm::mat4(1.0f), pos);
  auto rotation =
      glm::rotate(glm::mat4(1.0f), glm::radians(rot.x), {1.0, 0.0, 0.0});
  rotation = glm::rotate(rotation, glm::radians(rot.y), {0.0, 1.0, 0.0});
  rotation = glm::rotate(rotation, glm::radians(rot.z), {0.0, 0.0, 1.0});
  auto scaling = glm::scale(glm::mat4(1.0f), scale);

  auto model = translation * rotation * scaling;

  for (auto &node : m_nodes) {
    draw_node(node, model, shader);
  }
}

void GltfModel::draw_node(GltfNode &node, glm::mat4 &model,
                          gl::Shader &shader) {
  auto node_model = model * node.transform;

  if (node.mesh != -1) {
    auto &mesh = m_meshes[node.mesh];

    for (auto &ppair : mesh.primitives) {
      const auto &prim = ppair.second;

      if (prim.diffuse_texture_index != -1) {
        auto &texture = m_textures[prim.diffuse_texture_index];
        texture.bind(0);
        shader.set("texture_diffuse0", (u32)0);

        shader.set("is_textured", true);
      } else {
        shader.set("is_textured", false);
      }

      shader.set("model", node_model);

      if (prim.index_buffer_index != -1) {
        prim.va.bind();
        gl::Buffer &ib = m_buffers[prim.index_buffer_index];
        ib.bind(gl::ELEMENT_ARRAY_BUFFER);
        GL_CALL(
            glDrawElements(prim.mode, prim.index_count, prim.index_type, 0));
      } else {
        prim.va.bind();
        GL_CALL(glDrawArrays(prim.mode, 0, prim.vertex_count));
      }
    }
  }

  for (auto &child : node.children) {
    draw_node(child, node_model, shader);
  }
}
