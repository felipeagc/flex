#include <flex/flex.hpp>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

glm::vec3 lerp(glm::vec3 v1, glm::vec3 v2, float t) {
  return v1 + t * (v2 - v1);
}

int main() {
  flex::Window window("Hello", 800, 600);

  std::vector<flex::Vertex> vertices{
      {{.5f, .5f, .0f}, {}, {1.0, 1.0, 1.0}, {1.0, 1.0}},   // top right
      {{.5f, -.5f, .0f}, {}, {0.0, 0.0, 0.0}, {1.0, 0.0}},  // bottom right
      {{-.5f, -.5f, .0f}, {}, {1.0, 0.0, 0.0}, {0.0, 0.0}}, // bottom left
      {{-.5f, .5f, .0f}, {}, {0.0, 0.0, 1.0}, {0.0, 1.0}},  // top left
  };

  std::vector<unsigned int> indices{
      0, 1, 3, // first triangle
      1, 2, 3, // second triangle
  };

  // Mesh stuff
  flex::Mesh mesh(vertices, indices);

  flex::Model cube("models/cube/cube.obj");

  // Camera stuff
  flex::Camera3D camera(window.get_width(), window.get_height());

  // Shader stuff
  flex::gl::Shader shader("simple.vert", "simple.frag");

  window.set_relative_mouse(true);

  glm::vec3 camera_target = camera.get_pos();

  // Window stuff
  window.on_quit([&]() { std::cout << "Quit" << std::endl; });

  window.on_update([&](float delta) {
    glm::vec3 movement;
    float velocity = delta * 3.0f;

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

    camera_target += movement;
    glm::vec3 smoothed_pos =
        lerp(camera.get_pos(), camera_target, delta * 10.0f);

    camera.set_pos(smoothed_pos);

    if (window.get_relative_mouse()) {
      const float sensitivity = 0.1f;
      int x, y;
      window.get_relative_mouse_pos(&x, &y);
      camera.set_pitch(camera.get_pitch() - (y * sensitivity));
      camera.set_yaw(camera.get_yaw() + (x * sensitivity));
    }

    camera.update(window.get_width(), window.get_height());

    shader.set("view", camera.get_view_matrix());
    shader.set("proj", camera.get_projection_matrix());

    // Drawing stuff
    shader.set("model", glm::translate(glm::mat4(), {-2.0, 0.0, 0.0}));
    mesh.draw(shader);

    shader.set("model", glm::translate(glm::mat4(), {2.0, 0.0, 0.0}));
    cube.draw(shader);
  });

  window.on_key_down([&](flex::keyboard::Key key, bool repeat) {
    if (key == FLEX_KEY_ESCAPE) {
      window.set_relative_mouse(!window.get_relative_mouse());
    }
  });

  window.run();

  return 0;
}
