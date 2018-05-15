#include <flex/config.hpp>
#include <flex/gl/shader.hpp>
#include <flex/gl/vertex_array.hpp>
#include <flex/gl/vertex_buffer.hpp>
#include <flex/gl/vertex_layout.hpp>
#include <flex/window.hpp>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  flex::Window window("Hello", 800, 600);

  float vertices[] = {-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0};

  // VBO and VAO stuff

  flex::gl::VertexBuffer vb;
  vb.buffer(vertices, sizeof(vertices));

  flex::gl::VertexLayout layout;
  flex::gl::push_element<float>(layout, 3);

  flex::gl::VertexArray vao;
  vao.set_buffer(vb, layout);

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
