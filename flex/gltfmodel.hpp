#pragma once

#include "gl/gl.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "gl/vertex_array.hpp"
#include "model.hpp"
#include <map>
#include <memory>

namespace flex {
struct GltfPrimitive {
  gl::VertexArray va;

  int diffuse_texture_index;
  int index_buffer_index = -1;

  size_t index_count;
  GLenum index_type;
  size_t vertex_count;

  GLenum mode;
};

struct GltfMesh {
  std::map<int, GltfPrimitive> primitives;
};

struct GltfNode {
  int mesh = -1;
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
  std::map<int, gl::Buffer> m_buffers;
  std::map<int, GltfMesh> m_meshes;
  std::vector<GltfNode> m_nodes;
  std::map<int, gl::Texture> m_textures;

  void draw_node(GltfNode &node, glm::mat4 &model, gl::Shader &shader);
};
} // namespace flex
