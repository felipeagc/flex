#include "mesh_scene.hpp"

using namespace game;

void MeshScene::update(float delta) {
  camera.update(window.get_width(), window.get_height());
  camera.set_uniforms(shader);

  mesh.draw(shader, {0.0, 0.0, -5.0});
}
