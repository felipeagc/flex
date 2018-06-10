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

std::vector<glm::mat4> make_transforms(float time = 0) {
  std::vector<glm::mat4> transforms;
  float size = 15.0;
  int amount = 10;
  for (int x = -amount / 2; x < amount / 2; x++) {
    for (int y = -amount / 2; y < amount / 2; y++) {
      for (int z = -amount / 2; z < amount / 2; z++) {
        auto pos = glm::vec3(
            x * size, (y * size) + sin((time + x + z) * 2.0) * 2.0, z * size);
        auto translation = glm::translate(glm::mat4(1.0f), pos);
        auto scale = glm::scale(translation, glm::vec3(1.0));
        transforms.push_back(scale);
      }
    }
  }
  return transforms;
}

class MyApp : public flex::App {
private:
  std::vector<flex::Vertex> vertices{
      {{.5f, .5f, .0f}, {1.0, 1.0, 1.0}, {1.0, 1.0}},   // top right
      {{.5f, -.5f, .0f}, {1.0, 1.0, 1.0}, {1.0, 0.0}},  // bottom right
      {{-.5f, -.5f, .0f}, {1.0, 1.0, 1.0}, {0.0, 0.0}}, // bottom left
      {{-.5f, .5f, .0f}, {1.0, 1.0, 1.0}, {0.0, 1.0}},  // top left
  };

  std::vector<unsigned int> indices{
      0, 1, 3, // first triangle
      1, 2, 3, // second triangle
  };

  flex::gl::Shader m_shader{flex::path("shaders/simple.vert"),
                            flex::path("shaders/simple.frag")};
  flex::gl::Shader m_shader_instanced{flex::path("shaders/simple.vert"),
                                      flex::path("shaders/simple.frag"),
                                      {{"INSTANCED", "true"}}};

  flex::Mesh mesh{vertices, indices};
  // flex::InstancedModel cube{flex::path("models/cube.obj"),
  // make_transforms()};
  flex::InstancedGltfModel model{flex::path("models/helmet.glb"),
                                 make_transforms()};

  flex::Audio shot{flex::path("audio/shotgun.wav")};

  flex::Camera3D camera{400, 400};
  glm::vec3 camera_target{camera.get_pos()};

  flex::Canvas canvas{400, 400};

  flex::Sprite sprite{flex::path("sprites/sprite.png"),
                      flex::gl::FILTER_NEAREST};

  double elapsed_time = 0;

public:
  using flex::App::App;

  void load() { window.set_relative_mouse(true); }

  void quit() { flex::log("Quit"); }

  void camera_movement(float delta) {
    glm::vec3 movement{0.0};
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
  }

  void update(float delta) {
    elapsed_time += delta;
    camera_movement(delta);

    camera.update(window.get_width(), window.get_height());
    camera.set_uniforms(m_shader);
    camera.set_uniforms(m_shader_instanced);

    model.set_transforms(make_transforms(elapsed_time));

    // Drawing stuff
    {
      graphics.use_shader(m_shader_instanced);
      graphics.draw_instanced(model);
    }

    {
      graphics.use_shader(m_shader);

      // graphics.draw(model, {2.0, 0.0, 0.0}, {}, {50.0, 50.0, 50.0});
      // graphics.draw(model, {2.0, 0.0, 0.0});
      graphics.draw(mesh);
      graphics.draw(sprite, {-2.0, 0.0, 0.0});
    }

    {
      ImGui::Begin("Hello");
      ImGui::Text("FPS: %f", 1.0 / delta);
      ImGui::End();
    }
  }

  void key_down(flex::input::Key key, bool repeat) {
    if (key == FLEX_KEY_ESCAPE) {
      window.set_relative_mouse(!window.get_relative_mouse());
    }
    if (key == FLEX_KEY_SPACE && !repeat) {
      audio.play(shot, 0.1);
    }
  }

  void button_down(flex::input::MouseButton button, int x, int y) {
    audio.play(shot, 0.1);
  }
};

int main() {
  flex::Engine engine("Half-Life 3", 800, 600);
  MyApp app{engine};

  engine.get_window().run(app);

  return 0;
}
