#include "mesh.hpp"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

using namespace flex;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<std::shared_ptr<gl::Texture>> diffuse_textures,
           std::vector<std::shared_ptr<gl::Texture>> specular_textures,
           std::vector<std::shared_ptr<gl::Texture>> normal_textures,
           std::vector<std::shared_ptr<gl::Texture>> height_textures)
    : m_vertices(vertices), m_indices(indices),
      m_diffuse_textures(diffuse_textures),
      m_specular_textures(specular_textures),
      m_normal_textures(normal_textures), m_height_textures(height_textures) {
  m_vb->buffer(&vertices.data()[0], sizeof(Vertex) * vertices.size());

  flex::gl::VertexBufferLayout layout;
  layout.push_float(3); // position
  layout.push_float(3); // normal
  layout.push_float(3); // color
  layout.push_float(2); // tex_coords

  m_ib->buffer(&indices.data()[0], sizeof(GLuint) * indices.size());

  m_va->add_buffer(*m_vb, layout);
}

Mesh::~Mesh() {}

void Mesh::set_vertices(std::vector<Vertex> vertices) {
  if (vertices.size() == m_vertices.size()) {
    m_vb->buffer_sub_data(&vertices.data()[0], sizeof(Vertex) * vertices.size(),
                          0);
  } else {
    m_vb->buffer(&vertices.data()[0], sizeof(Vertex) * vertices.size());
  }

  m_vertices = vertices;
}

void Mesh::set_indices(std::vector<GLuint> indices) {
  if (indices.size() == m_indices.size()) {
    m_ib->buffer_sub_data(&indices.data()[0], sizeof(GLuint) * indices.size(),
                          0);
  } else {
    m_ib->buffer(&indices.data()[0], sizeof(GLuint) * indices.size());
  }

  m_indices = indices;
}

void Mesh::set_vertices_and_indices(std::vector<Vertex> vertices,
                                    std::vector<GLuint> indices) {
  this->set_vertices(vertices);
  this->set_indices(indices);
}

void Mesh::add_diffuse_texture(std::shared_ptr<gl::Texture> texture) {
  this->m_diffuse_textures.push_back(texture);
}

void Mesh::add_specular_texture(std::shared_ptr<gl::Texture> texture) {
  this->m_specular_textures.push_back(texture);
}

void Mesh::add_normal_texture(std::shared_ptr<gl::Texture> texture) {
  this->m_normal_textures.push_back(texture);
}

void Mesh::add_height_texture(std::shared_ptr<gl::Texture> texture) {
  this->m_height_textures.push_back(texture);
}

void Mesh::set_texture_filter(gl::TextureFilter filter) {
  for (auto &tex : m_diffuse_textures) {
    tex->set_filter(filter);
  }
  for (auto &tex : m_specular_textures) {
    tex->set_filter(filter);
  }
  for (auto &tex : m_normal_textures) {
    tex->set_filter(filter);
  }
  for (auto &tex : m_height_textures) {
    tex->set_filter(filter);
  }
}

void Mesh::bind_textures(gl::Shader &shader) {
  unsigned int n = 0;

  for (unsigned int i = 0; i < m_diffuse_textures.size(); i++) {
    m_diffuse_textures[i]->bind(n);
    shader.set("texture_diffuse" + std::to_string(i), n);
    n++;
  }

  for (unsigned int i = 0; i < m_specular_textures.size(); i++) {
    m_specular_textures[i]->bind(n);
    shader.set("texture_specular" + std::to_string(i), n);
    n++;
  }

  for (unsigned int i = 0; i < m_normal_textures.size(); i++) {
    m_normal_textures[i]->bind(n);
    shader.set("texture_normal" + std::to_string(i), n);
    n++;
  }

  for (unsigned int i = 0; i < m_height_textures.size(); i++) {
    m_height_textures[i]->bind(n);
    shader.set("texture_height" + std::to_string(i), n);
    n++;
  }

  shader.set("is_textured", n != 0);
}

void Mesh::draw(GraphicsSystem &graphics, glm::vec3 pos, glm::vec3 rot,
                glm::vec3 scale) {
  auto shader = graphics.get_shader();
  if (shader == nullptr) {
    flex::log(L_WARN, L_RENDER,
              "Couldn't draw mesh: no shader currently bound");
    return;
  }

  auto translation = glm::translate(glm::mat4(1.0f), pos);
  auto rotation =
      glm::rotate(glm::mat4(1.0f), glm::radians(rot.x), {1.0, 0.0, 0.0});
  rotation = glm::rotate(rotation, glm::radians(rot.y), {0.0, 1.0, 0.0});
  rotation = glm::rotate(rotation, glm::radians(rot.z), {0.0, 0.0, 1.0});
  auto scaling = glm::scale(glm::mat4(1.0f), scale);

  auto model = translation * rotation * scaling;

  shader->set("model", model);

  this->bind_textures(*shader);

  m_va->bind();
  m_ib->bind();
  gl::draw_elements(m_indices.size());
}
