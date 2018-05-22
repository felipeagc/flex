#include "mesh.hpp"

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
  m_vb.buffer(&vertices.data()[0], sizeof(Vertex) * vertices.size());

  flex::gl::VertexBufferLayout layout;
  layout.push_float(3); // position
  layout.push_float(3); // normal
  layout.push_float(3); // color
  layout.push_float(2); // tex_coords

  m_ib.buffer(&indices.data()[0], sizeof(GLuint) * indices.size());

  m_va.add_buffer(m_vb, layout);
}

Mesh::~Mesh() {}

void Mesh::draw(gl::Shader &shader) {
  shader.use();

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

  m_va.bind();
  m_ib.bind();
  GL_CALL(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0));
}

void Mesh::set_vertices(std::vector<Vertex> vertices) {
  if (vertices.size() == m_vertices.size()) {
    m_vb.buffer_sub_data(&vertices.data()[0], sizeof(Vertex) * vertices.size(),
                         0);
  } else {
    m_vb.buffer(&vertices.data()[0], sizeof(Vertex) * vertices.size());
  }

  m_vertices = vertices;
}

void Mesh::set_indices(std::vector<GLuint> indices) {
  if (indices.size() == m_indices.size()) {
    m_ib.buffer_sub_data(&indices.data()[0], sizeof(GLuint) * indices.size(),
                         0);
  } else {
    m_ib.buffer(&indices.data()[0], sizeof(GLuint) * indices.size());
  }

  m_indices = indices;
}

void Mesh::set_vertices_and_indices(std::vector<Vertex> vertices,
                                    std::vector<GLuint> indices) {
  this->set_vertices(vertices);
  this->set_indices(indices);
}
