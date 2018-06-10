#pragma once

#include <flex/flex.hpp>

namespace game {
class MeshScene : public flex::EventHandler {
public:
  using flex::EventHandler::EventHandler;

  virtual void update(float delta) override;

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

  flex::Mesh mesh{vertices, indices};

  flex::Camera3D camera{window.get_width(), window.get_height()};

  flex::gl::Shader shader{flex::path("shaders/simple.vert"),
                          flex::path("shaders/simple.frag")};
};
} // namespace game
