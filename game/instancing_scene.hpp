#pragma once

#include <flex/flex.hpp>

namespace game {
class InstancingScene : public flex::EventHandler {
public:
  using flex::EventHandler::EventHandler;

  virtual void update(float delta) override;

private:
  double elapsed_time = 0;

  std::vector<glm::mat4> make_transforms(float time = 0);
  void camera_movement(float delta);

  flex::Camera3D camera{window.get_width(), window.get_height()};
  glm::vec3 camera_target{camera.get_pos()};

  flex::gl::Shader shader_instanced{flex::path("shaders/simple.vert"),
                                    flex::path("shaders/simple.frag"),
                                    {{"INSTANCED", "true"}}};

  flex::InstancedGltfModel model{flex::path("models/helmet.glb"),
                                 make_transforms()};
};
} // namespace game
