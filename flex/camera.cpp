#include "camera.hpp"

using namespace flex;

Camera3D::Camera3D(int width, int height, glm::vec3 position, glm::vec3 up,
                   float yaw, float pitch) {
  m_pos = position;
  m_world_up = up;
  m_yaw = yaw;
  m_pitch = pitch;
  this->update(width, height);
}

Camera3D::~Camera3D() {}

glm::mat4 Camera3D::get_view_matrix() {
  return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

glm::mat4 Camera3D::get_projection_matrix() { return m_projection; }

void Camera3D::update(int width, int height) {
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front = glm::normalize(front);

  m_right = glm::normalize(glm::cross(m_front, m_world_up));
  m_up = glm::normalize(glm::cross(m_right, m_front));

  m_projection = glm::perspective(glm::radians(m_fov),
                                  (float)width / (float)height, 0.1f, 300.0f);
}

void Camera3D::set_pos(glm::vec3 pos) { m_pos = pos; }

glm::vec3 Camera3D::get_pos() const { return m_pos; }

void Camera3D::set_yaw(float yaw) { m_yaw = yaw; }

float Camera3D::get_yaw() const { return m_yaw; }

void Camera3D::set_pitch(float pitch) {
  if (pitch > 89.0f)
    m_pitch = 89.0f;
  else if (pitch < -89.0f)
    m_pitch = -89.0f;
  else
    m_pitch = pitch;
}

float Camera3D::get_pitch() const { return m_pitch; }

void Camera3D::set_fov(float fov) { m_fov = fov; }

float Camera3D::get_fov() const { return m_fov; }

glm::vec3 Camera3D::get_front() const { return m_front; }

glm::vec3 Camera3D::get_right() const { return m_right; }
