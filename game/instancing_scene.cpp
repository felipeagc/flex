#include "instancing_scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace game;

std::vector<glm::mat4> InstancingScene::make_transforms(f32 time) {
  std::vector<glm::mat4> transforms;
  f32 size = 10.0;
  i32 amount = 5;
  for (i32 x = -amount / 2; x < amount / 2; x++) {
    for (i32 y = -amount / 2; y < amount / 2; y++) {
      for (i32 z = -amount / 2; z < amount / 2; z++) {
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

void InstancingScene::camera_movement(f32 delta) {
  glm::vec3 movement{0.0};
  f32 velocity = delta * 10.0f;

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
      flex::lerp(camera.get_pos(), camera_target, delta * 10.0f);

  camera.set_pos(smoothed_pos);

  if (window.get_relative_mouse()) {
    const f32 sensitivity = 0.1f;
    i32 x, y;
    window.get_relative_mouse_pos(&x, &y);
    camera.set_pitch(camera.get_pitch() - (y * sensitivity));
    camera.set_yaw(camera.get_yaw() + (x * sensitivity));
  }
}

void InstancingScene::update(f32 delta) {
  elapsed_time += delta;
  camera_movement(delta);

  camera.update(window.get_width(), window.get_height());
  camera.set_uniforms(shader_instanced);

  model.set_transforms(make_transforms(elapsed_time));

  // Drawing stuff
  model.draw_instanced(shader_instanced);
}
