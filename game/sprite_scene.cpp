#include "sprite_scene.hpp"

using namespace game;

void SpriteScene::update(float delta) {
  glm::vec2 movement(0.0);
  float velocity = delta * 100.0;
  if (window.is_key_pressed(FLEX_SCANCODE_W)) {
    movement -= glm::vec2(0.0, velocity);
  }
  if (window.is_key_pressed(FLEX_SCANCODE_S)) {
    movement += glm::vec2(0.0, velocity);
  }
  if (window.is_key_pressed(FLEX_SCANCODE_D)) {
    movement -= glm::vec2(velocity, 0.0);
  }
  if (window.is_key_pressed(FLEX_SCANCODE_A)) {
    movement += glm::vec2(velocity, 0.0);
  }

  camera.set_pos(camera.get_pos() + movement);
  camera.set_uniforms(shader);

  sprite.draw(shader, {-100.0, 0.0}, 0.0, {5.0, 5.0});

  sprite.draw(shader, {0.0, 0.0}, 30.0, {5.0, 5.0});

  sprite.draw(shader, {100.0, 100.0}, -30.0, {5.0, 5.0});
}

void SpriteScene::resized(unsigned int w, unsigned int h) {
  camera.update(window.get_width(), window.get_height());
}

void SpriteScene::mouse_wheel(int x, int y) {
  if (window.is_key_pressed(FLEX_SCANCODE_LCTRL)) {
    camera.set_rot(camera.get_rot() + (float) y * 2.0);
  } else {
    glm::vec2 delta = {(float)y / 2.0, (float)y / 2.0};
    if ((camera.get_scale() + delta).x > 0.0) {
      camera.set_scale(camera.get_scale() + delta);
    }
  }
}
