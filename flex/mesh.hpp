#pragma once

#include "gl/index_buffer.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "gl/vertex_array.hpp"
#include "gl/vertex_buffer.hpp"
#include "gl/vertex_buffer_layout.hpp"
#include <algorithm>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace flex {
struct Vertex {
  glm::vec3 pos;
  glm::vec3 normal;
  glm::vec3 color;
  glm::vec2 tex_coords;
};

class Mesh {
public:
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
       std::vector<std::shared_ptr<gl::Texture>> diffuse_textures = {},
       std::vector<std::shared_ptr<gl::Texture>> specular_textures = {},
       std::vector<std::shared_ptr<gl::Texture>> normal_textures = {},
       std::vector<std::shared_ptr<gl::Texture>> height_textures = {});

  ~Mesh();

  void draw(gl::Shader &shader);

  void set_vertices(std::vector<Vertex> vertices);
  void set_indices(std::vector<GLuint> indices);
  void set_vertices_and_indices(std::vector<Vertex> vertices,
                                std::vector<GLuint> indices);

private:
  gl::VertexBuffer m_vb;
  gl::IndexBuffer m_ib;
  gl::VertexArray m_va;

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  std::vector<std::shared_ptr<gl::Texture>> m_diffuse_textures;
  std::vector<std::shared_ptr<gl::Texture>> m_specular_textures;
  std::vector<std::shared_ptr<gl::Texture>> m_normal_textures;
  std::vector<std::shared_ptr<gl::Texture>> m_height_textures;
};
} // namespace flex
