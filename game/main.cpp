#include <flex/camera.hpp>
#include <flex/config.hpp>
#include <flex/gl/shader.hpp>
#include <flex/mesh.hpp>
#include <flex/scancodes.hpp>
#include <flex/window.hpp>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  flex::Window window("Hello", 800, 600);

  std::vector<flex::Vertex> vertices{
      {{.5f, .5f, .0f}, {1.0, 1.0, 1.0}},   // top right
      {{.5f, -.5f, .0f}, {0.0, 0.0, 0.0}},  // bottom right
      {{-.5f, -.5f, .0f}, {1.0, 0.0, 0.0}}, // bottom left
      {{-.5f, .5f, .0f}, {0.0, 0.0, 1.0}},  // top left
  };

  std::vector<unsigned int> indices{
      0, 1, 3, // first triangle
      1, 2, 3, // second triangle
  };

  // Mesh stuff
  flex::Mesh mesh(vertices, indices);

  // Camera stuff
  flex::Camera3D camera(window.get_width(), window.get_height());

  // Shader stuff
  flex::gl::Shader shader("simple.vert", "simple.frag");

  glm::mat4 model = glm::translate(glm::mat4(1.0f), {0.0, 0.0, 0.0});
  shader.set("model", model);

  window.set_relative_mouse(true);

  // Window stuff
  window.on_quit([&]() { std::cout << "Quit" << std::endl; });

  window.on_update([&](float delta) {
    glm::vec3 movement;
    float velocity = delta * 10.0f;

    if (window.is_key_pressed(FLEX_SCANCODE_W)) {
      movement += camera.get_front() * velocity;
    }
    if (window.is_key_pressed(FLEX_SCANCODE_S)) {
      movement += camera.get_front() * -velocity;
    }
    if (window.is_key_pressed(FLEX_SCANCODE_A)) {
      movement += camera.get_right() * -velocity;
    }
    if (window.is_key_pressed(FLEX_SCANCODE_D)) {
      movement += camera.get_right() * velocity;
    }

    camera.set_pos(camera.get_pos() + movement);

    const float sensitivity = 0.1f;
    int x, y;
    window.get_relative_mouse_pos(&x, &y);
    camera.set_pitch(camera.get_pitch() - (y * sensitivity));
    camera.set_yaw(camera.get_yaw() + (x * sensitivity));

    camera.update(window.get_width(), window.get_height());

    shader.set("view", camera.get_view_matrix());
    shader.set("proj", camera.get_projection_matrix());

    // Drawing stuff
    mesh.draw(shader);
  });

  window.run();

  return 0;
}
