#pragma once

#include <flex/gl/shader.hpp>
#include <flex/gl/vertex_buffer.hpp>
#include <flex/gl/index_buffer.hpp>
#include <flex/gl/vertex_array.hpp>
#include <flex/gl/vertex_buffer_layout.hpp>
#include <vector>
#include <glm/glm.hpp>

namespace flex {
  struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
  };

  class Mesh {
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    ~Mesh();

    void draw(const gl::Shader &shader);

  private:
    gl::VertexBuffer m_vb;
    gl::IndexBuffer m_ib;
    gl::VertexArray m_va;

    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
  };
}
