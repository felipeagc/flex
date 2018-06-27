#include "canvas_scene.hpp"

using namespace game;

void CanvasScene::camera_movement(float delta) {
  glm::vec3 movement{0.0};
  float velocity = delta * 10.0f;

  if (window.is_key_pressed(FLEX_SCANCODE_W)) {
    movement += canvas_camera.get_front() * velocity;
  }
  if (window.is_key_pressed(FLEX_SCANCODE_S)) {
    movement += canvas_camera.get_front() * -velocity;
  }
  if (window.is_key_pressed(FLEX_SCANCODE_A)) {
    movement += canvas_camera.get_right() * -velocity;
  }
  if (window.is_key_pressed(FLEX_SCANCODE_D)) {
    movement += canvas_camera.get_right() * velocity;
  }

  camera_target += movement;
  glm::vec3 smoothed_pos = flex::lerp(canvas_camera.get_pos(), camera_target, delta * 10.0f);

  canvas_camera.set_pos(smoothed_pos);

  if (window.get_relative_mouse()) {
    const float sensitivity = 0.1f;
    int x, y;
    window.get_relative_mouse_pos(&x, &y);
    canvas_camera.set_pitch(canvas_camera.get_pitch() - (y * sensitivity));
    canvas_camera.set_yaw(canvas_camera.get_yaw() + (x * sensitivity));
  }
}

void CanvasScene::update(float delta) {
  // Canvas drawing
  canvas.bind();
  {
    flex::gl::clear_color(1.0, 0.0, 0.0, 1.0);
    flex::gl::clear_buffers();

    camera_movement(delta);

    canvas_camera.update(canvas.get_width(), canvas.get_height());
    canvas_camera.set_uniforms(canvas_shader);

    // TODO: fix the texture blurriness
    sprite.draw(canvas_shader);
    model.draw(canvas_shader, {2.0, 0.0, 0.0});
  }
  canvas.unbind(window);

  // Draw the canvas
  camera.update(window.get_width(), window.get_height());
  camera.set_uniforms(shader);

  canvas.draw(shader);
}

void CanvasScene::resized(unsigned int w, unsigned int h) {
  canvas.resize(w/2, h/2);
}
