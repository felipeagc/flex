#pragma once

#include "gl/shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace flex {
class Camera3D {
public:
  Camera3D(int width, int height, glm::vec3 position = glm::vec3{0.0},
           float fov = 70.0f, glm::vec3 up = {0, 1.0f, 0}, float yaw = -90.0f,
           float pitch = 0);
  virtual ~Camera3D() {};

  glm::mat4 get_view_matrix();
  glm::mat4 get_projection_matrix();
  void update(int width, int height);
  void set_uniforms(gl::Shader &shader);

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

  float m_near = 0.01f;
  float m_far = 300.0f;

  void update_projection(int width, int height);
  void update_directions();
};

class Camera2D {
public:
  Camera2D(int width, int height, glm::vec2 pos = glm::vec2(0.0),
           float rotation = 0.0, glm::vec2 scale = glm::vec2(1.0));
  virtual ~Camera2D() {};

  glm::mat4 get_view_matrix();
  glm::mat4 get_projection_matrix();

  void update(int width, int height);
  void set_uniforms(gl::Shader &shader);

  void set_pos(glm::vec2 pos);
  glm::vec2 get_pos() const;

  void set_rot(float degrees);
  float get_rot() const;

  void set_scale(glm::vec2 scale);
  glm::vec2 get_scale() const;

private:
  void update_projection(int width, int height);

  float m_near = 0.00f;
  float m_far = 300.0f;

  glm::vec2 m_pos;
  float m_rotation;
  glm::vec2 m_scale;

  glm::mat4 m_projection;
};
} // namespace flex
