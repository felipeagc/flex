#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace flex {
class Camera3D {
public:
  Camera3D(int width, int height, glm::vec3 position = {}, float fov = 70.0f,
           glm::vec3 up = {0, 1.0f, 0}, float yaw = -90.0f, float pitch = 0);
  ~Camera3D();

  glm::mat4 get_view_matrix();
  glm::mat4 get_projection_matrix();
  void update(int width, int height);

  void set_pos(glm::vec3 pos);
  glm::vec3 get_pos() const;

  void set_yaw(float yaw);
  float get_yaw() const;

  void set_pitch(float pitch);
  float get_pitch() const;

  void set_fov(float fov);
  float get_fov() const;

  glm::vec3 get_front() const;
  glm::vec3 get_right() const;

private:
  glm::vec3 m_pos;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_world_up;

  glm::mat4 m_projection;

  float m_yaw;
  float m_pitch;
  float m_fov;
};
} // namespace flex
