#include <flex/window.hpp>
#include <flex/config.hpp>
#include <flex/gl/shader.hpp>
#include <flex/gl/vertex_buffer.hpp>
#include <flex/gl/vertex_array.hpp>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main() {
  flex::Window window("Hello", 800, 600);

  float vertices[] = {
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.0, 0.5, 0.0
  };

  // VBO and VAO stuff

  flex::gl::VertexBuffer vbo;
  flex::gl::VertexArray vao;

  vao.bind();

  vbo.buffer(vertices, sizeof(vertices));

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  // Shader stuff
  flex::gl::Shader shader("simple.glslv", "simple.glslf");

  // Window stuff

  window.on_quit([&]() {
    std::cout << "Quit" << std::endl;
  });

  window.on_update([&](float delta) {
      // Drawing stuff
      shader.use();
      vao.bind();
      glDrawArrays(GL_TRIANGLES, 0, 3);
  });

  window.run();

  return 0;
}
