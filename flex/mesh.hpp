#pragma once

#include "drawable.hpp"
#include "gl/buffer.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "gl/vertex_array.hpp"
#include "gl/vertex_buffer_layout.hpp"
#include "types.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace flex {
struct Vertex {
  glm::vec3 pos;
  glm::vec3 normal;
  glm::vec2 tex_coords;
};

class Mesh : public Drawable {
public:
  Mesh(std::vector<Vertex> vertices, std::vector<u32> indices,
       std::vector<gl::Texture> diffuse_textures = {},
       std::vector<gl::Texture> specular_textures = {},
       std::vector<gl::Texture> normal_textures = {},
       std::vector<gl::Texture> height_textures = {});

  virtual ~Mesh();

  void set_vertices(std::vector<Vertex> vertices);
  void set_indices(std::vector<u32> indices);
  void set_vertices_and_indices(std::vector<Vertex> vertices,
                                std::vector<u32> indices);

  void add_diffuse_texture(gl::Texture texture);
  void add_specular_texture(gl::Texture texture);
  void add_normal_texture(gl::Texture texture);
  void add_height_texture(gl::Texture texture);

  void draw(gl::Shader &shader, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0),
            glm::vec3 scale = glm::vec3(1.0)) override;

protected:
  void bind_textures(gl::Shader &shader);

  gl::Buffer m_vb;
  gl::Buffer m_ib;
  gl::VertexArray m_va;

  std::vector<Vertex> m_vertices;
  std::vector<u32> m_indices;
  std::vector<gl::Texture> m_diffuse_textures;
  std::vector<gl::Texture> m_specular_textures;
  std::vector<gl::Texture> m_normal_textures;
  std::vector<gl::Texture> m_height_textures;
};
} // namespace flex
