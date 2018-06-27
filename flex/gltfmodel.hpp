#pragma once

#include "gl/gl.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "gl/vertex_array.hpp"
#include "model.hpp"
#include "types.hpp"
#include <map>

namespace flex {
struct GltfPrimitive {
  gl::VertexArray va;

  i32 diffuse_texture_index;
  i32 index_buffer_index = -1;

  size_t index_count;
  GLenum index_type;
  size_t vertex_count;

  GLenum mode;
};

struct GltfMesh {
  std::map<i32, GltfPrimitive> primitives;
};

struct GltfNode {
  i32 mesh = -1;
  glm::mat4 transform;
  std::vector<GltfNode> children;
};

class GltfModel : public Model {
public:
  GltfModel(const std::string &path);
  ~GltfModel();

  void draw(gl::Shader &shader, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0),
            glm::vec3 scale = glm::vec3(1.0)) override;

protected:
  std::map<i32, gl::Buffer> m_buffers;
  std::map<i32, GltfMesh> m_meshes;
  std::vector<GltfNode> m_nodes;
  std::map<i32, gl::Texture> m_textures;

  void draw_node(GltfNode &node, glm::mat4 &model, gl::Shader &shader);
};
} // namespace flex
