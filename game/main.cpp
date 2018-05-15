#include <flex/config.hpp>
#include <flex/mesh.hpp>
#include <flex/gl/shader.hpp>
#include <flex/window.hpp>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  flex::Window window("Hello", 800, 600);

  std::vector<flex::Vertex> vertices{
    { { .5f, .5f, .0f }, { 1.0, 1.0, 1.0 } }, // top right
    { { .5f, -.5f, .0f }, { 0.0, 0.0, 0.0 } }, // bottom right
    { { -.5f, -.5f, .0f }, { 1.0, 0.0, 0.0 } }, // bottom left
    { { -.5f, .5f, .0f }, { 0.0, 0.0, 1.0 } }, // top left
  };

  std::vector<unsigned int> indices{
      0, 1, 3, // first triangle
      1, 2, 3, // second triangle
  };

  // Mesh stuff
  flex::Mesh mesh(vertices, indices);

  // Shader stuff
  flex::gl::Shader shader("simple.glslv", "simple.glslf");

  // Window stuff
  window.on_quit([&]() { std::cout << "Quit" << std::endl; });

  window.on_update([&](float delta) {
    // Drawing stuff
    mesh.draw(shader);

    // vao.bind();
    // ib.bind();
    // GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
  });

  window.run();

  return 0;
}
