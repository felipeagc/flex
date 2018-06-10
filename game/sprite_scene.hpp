#pragma once

#include <flex/flex.hpp>

namespace game {
class SpriteScene : public flex::EventHandler {
public:
  using flex::EventHandler::EventHandler;

  virtual void update(float delta) override;

private:
  // TODO: replace with Camera2D
  flex::Camera3D camera{window.get_width(), window.get_height()};

  flex::gl::Shader shader{flex::path("shaders/simple.vert"),
                          flex::path("shaders/simple.frag")};

  flex::Sprite sprite{flex::path("sprites/sprite.png"),
                      flex::gl::FILTER_NEAREST};
};
} // namespace game
