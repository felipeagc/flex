#pragma once

#include <flex/flex.hpp>

namespace game {
class CanvasScene : public flex::EventHandler {
public:
  using flex::EventHandler::EventHandler;

  virtual void update(f32 delta) override;
  virtual void resized(u32 w, u32 h) override;

  void camera_movement(f32 delta);

private:
  flex::Canvas canvas{400, 300};

  flex::Camera2D camera{window.get_width(), window.get_height()};

  flex::Camera3D canvas_camera{canvas.get_width(), canvas.get_height()};
  glm::vec3 camera_target{canvas_camera.get_pos()};

  flex::gl::Shader canvas_shader{flex::path("shaders/simple.vert"),
                          flex::path("shaders/simple.frag")};

  flex::gl::Shader shader{flex::path("shaders/simple.vert"),
                          flex::path("shaders/simple.frag")};

  flex::Sprite sprite{flex::path("sprites/sprite.png"),
                      flex::gl::FILTER_NEAREST};

  flex::GltfModel model{flex::path("models/helmet.glb")};

};
} // namespace game
