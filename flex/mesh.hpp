#pragma once

#include "drawable.hpp"
#include "gl/index_buffer.hpp"
#include "gl/shader.hpp"
#include "gl/texture.hpp"
#include "gl/vertex_array.hpp"
#include "gl/vertex_buffer.hpp"
#include "gl/vertex_buffer_layout.hpp"
#include "graphics.hpp"
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

class Mesh : public Drawable {
public:
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
       std::vector<std::shared_ptr<gl::Texture>> diffuse_textures = {},
       std::vector<std::shared_ptr<gl::Texture>> specular_textures = {},
       std::vector<std::shared_ptr<gl::Texture>> normal_textures = {},
       std::vector<std::shared_ptr<gl::Texture>> height_textures = {});

  ~Mesh();

  void set_vertices(std::vector<Vertex> vertices);
  void set_indices(std::vector<GLuint> indices);
  void set_vertices_and_indices(std::vector<Vertex> vertices,
                                std::vector<GLuint> indices);

  void add_diffuse_texture(std::shared_ptr<gl::Texture> texture);
  void add_specular_texture(std::shared_ptr<gl::Texture> texture);
  void add_normal_texture(std::shared_ptr<gl::Texture> texture);
  void add_height_texture(std::shared_ptr<gl::Texture> texture);

  void set_texture_filter(gl::TextureFilter filter);

protected:
  void draw(GraphicsSystem &graphics, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0),
            glm::vec3 scale = glm::vec3(1.0)) override;

  void bind_textures(gl::Shader &shader);

  std::shared_ptr<gl::VertexBuffer> m_vb = std::make_shared<gl::VertexBuffer>();
  std::shared_ptr<gl::IndexBuffer> m_ib = std::make_shared<gl::IndexBuffer>();
  std::shared_ptr<gl::VertexArray> m_va = std::make_shared<gl::VertexArray>();

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  std::vector<std::shared_ptr<gl::Texture>> m_diffuse_textures;
  std::vector<std::shared_ptr<gl::Texture>> m_specular_textures;
  std::vector<std::shared_ptr<gl::Texture>> m_normal_textures;
  std::vector<std::shared_ptr<gl::Texture>> m_height_textures;
};
} // namespace flex
