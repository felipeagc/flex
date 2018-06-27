#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace flex;

Camera3D::Camera3D(u32 width, u32 height, glm::vec3 position, f32 fov,
                   glm::vec3 up, f32 yaw, f32 pitch) {
  m_pos = position;
  m_fov = fov;
  m_world_up = up;
  m_yaw = yaw;
  m_pitch = pitch;

  this->update_directions();
  this->update_projection(width, height);
}

glm::mat4 Camera3D::get_view_matrix() {
  return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

glm::mat4 Camera3D::get_projection_matrix() { return m_projection; }

void Camera3D::update(u32 width, u32 height) {
  this->update_directions();
  this->update_projection(width, height);
}

void Camera3D::set_uniforms(gl::Shader &shader) {
  shader.set("view", get_view_matrix());
  shader.set("proj", get_projection_matrix());
}

void Camera3D::set_pos(glm::vec3 pos) { m_pos = pos; }

glm::vec3 Camera3D::get_pos() const { return m_pos; }

void Camera3D::set_yaw(f32 yaw) { m_yaw = yaw; }

f32 Camera3D::get_yaw() const { return m_yaw; }

void Camera3D::set_pitch(f32 pitch) {
  if (pitch > 89.0f)
    m_pitch = 89.0f;
  else if (pitch < -89.0f)
    m_pitch = -89.0f;
  else
    m_pitch = pitch;
}

f32 Camera3D::get_pitch() const { return m_pitch; }

void Camera3D::set_fov(f32 fov) { m_fov = fov; }

f32 Camera3D::get_fov() const { return m_fov; }

glm::vec3 Camera3D::get_front() const { return m_front; }

glm::vec3 Camera3D::get_right() const { return m_right; }

void Camera3D::update_projection(u32 width, u32 height) {
  m_projection = glm::perspective(glm::radians(m_fov), (f32)width / (f32)height,
                                  m_near, m_far);
}

void Camera3D::update_directions() {
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front = glm::normalize(front);

  m_right = glm::normalize(glm::cross(m_front, m_world_up));
  m_up = glm::normalize(glm::cross(m_right, m_front));
}

Camera2D::Camera2D(u32 width, u32 height, glm::vec2 pos, f32 rotation,
                   glm::vec2 scale) {
  m_pos = pos;
  m_rotation = rotation;
  m_scale = scale;

  this->update_projection(width, height);
}

glm::mat4 Camera2D::get_view_matrix() {
  auto translation =
      glm::translate(glm::mat4(1.0), glm::vec3(m_pos.x, m_pos.y, 0.0));
  auto rotation =
      glm::rotate(glm::mat4(1.0), glm::radians(m_rotation), {0.0, 0.0, 1.0});
  auto scale = glm::scale(glm::mat4(1.0), {m_scale.x, m_scale.y, 1.0});

  return scale * rotation * translation;
}

glm::mat4 Camera2D::get_projection_matrix() { return m_projection; }

void Camera2D::update(u32 width, u32 height) {
  this->update_projection(width, height);
}

void Camera2D::set_uniforms(gl::Shader &shader) {
  shader.set("view", get_view_matrix());
  shader.set("proj", get_projection_matrix());
}

void Camera2D::set_pos(glm::vec2 pos) { m_pos = pos; }

glm::vec2 Camera2D::get_pos() const { return m_pos; }

void Camera2D::set_rot(f32 degrees) { m_rotation = degrees; }

f32 Camera2D::get_rot() const { return m_rotation; }

void Camera2D::set_scale(glm::vec2 scale) { m_scale = scale; }

glm::vec2 Camera2D::get_scale() const { return m_scale; }

void Camera2D::update_projection(u32 width, u32 height) {
  m_projection = glm::ortho(-((f32)width) / 2, (f32)width / 2, -(f32)height / 2,
                            (f32)height / 2, m_near, m_far);
}
