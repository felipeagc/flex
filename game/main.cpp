#include <flex/config.hpp>
#include <flex/gl/shader.hpp>
#include <flex/gl/vertex_array.hpp>
#include <flex/gl/vertex_buffer.hpp>
#include <flex/gl/vertex_buffer_layout.hpp>
#include <flex/window.hpp>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  flex::Window window("Hello", 800, 600);

  float positions[] = {-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0};
  float colors[] = {1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0};

  // VBO and VAO stuff

  flex::gl::VertexBuffer vb_positions;
  vb_positions.buffer(positions, sizeof(positions));

  flex::gl::VertexBufferLayout pos_layout;
  flex::gl::push_element<float>(pos_layout, 3);

  flex::gl::VertexBuffer vb_colors;
  vb_colors.buffer(colors, sizeof(colors));

  flex::gl::VertexBufferLayout colors_layout;
  flex::gl::push_element<float>(colors_layout, 3);

  flex::gl::VertexArray vao;
  vao.add_buffer(vb_positions, pos_layout);
  vao.add_buffer(vb_colors, colors_layout);

  // Shader stuff
  flex::gl::Shader shader("simple.glslv", "simple.glslf");

  // Window stuff

  window.on_quit([&]() { std::cout << "Quit" << std::endl; });

  window.on_update([&](float delta) {
    // Drawing stuff
    shader.use();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  });

  window.run();

  return 0;
}
