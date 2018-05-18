#include "mesh.hpp"

using namespace flex;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
    : m_vertices(vertices), m_indices(indices) {
  m_vb.buffer(&vertices.data()[0], sizeof(Vertex) * vertices.size());

  flex::gl::VertexBufferLayout layout;
  layout.push_float(3); // position
  layout.push_float(3); // color

  m_ib.buffer(&indices.data()[0], sizeof(GLuint) * indices.size());

  m_va.add_buffer(m_vb, layout);
}

Mesh::~Mesh() {}

void Mesh::draw(const gl::Shader &shader) {
  shader.use();

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
