#pragma once

#include <flex/flex.hpp>

namespace game {
class SpriteScene : public flex::EventHandler {
public:
  using flex::EventHandler::EventHandler;

  virtual void update(f32 delta) override;
  virtual void mouse_wheel(i32 x, i32 y) override;
  virtual void resized(u32 w, u32 h) override;

private:
  flex::Camera2D camera{window.get_width(), window.get_height()};

  flex::gl::Shader shader{flex::path("shaders/simple.vert"),
                          flex::path("shaders/simple.frag")};

  flex::Sprite sprite{flex::path("sprites/sprite.png"),
                      flex::gl::FILTER_NEAREST};
};
} // namespace game
