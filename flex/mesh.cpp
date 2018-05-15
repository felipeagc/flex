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
