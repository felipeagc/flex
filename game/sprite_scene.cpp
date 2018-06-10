#include "sprite_scene.hpp"

using namespace game;

void SpriteScene::update(float delta) {
  camera.update(window.get_width(), window.get_height());
  camera.set_uniforms(shader);

  sprite.draw(shader, {0.0, 0.0, -5.0});
}
