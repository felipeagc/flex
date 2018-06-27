#pragma once

#include "gl/shader.hpp"
#include "types.hpp"
#include <glm/glm.hpp>

namespace flex {
class Camera3D {
public:
  Camera3D(u32 width, u32 height,
           glm::vec3 position = glm::vec3{0.0}, f32 fov = 70.0f,
           glm::vec3 up = {0, 1.0f, 0}, f32 yaw = -90.0f, f32 pitch = 0);
  virtual ~Camera3D(){};

  glm::mat4 get_view_matrix();
  glm::mat4 get_projection_matrix();
  void update(u32 width, u32 height);
  void set_uniforms(gl::Shader &shader);

  void set_pos(glm::vec3 pos);
  glm::vec3 get_pos() const;

  void set_yaw(f32 yaw);
  f32 get_yaw() const;

  void set_pitch(f32 pitch);
  f32 get_pitch() const;

  void set_fov(f32 fov);
  f32 get_fov() const;

  glm::vec3 get_front() const;
  glm::vec3 get_right() const;

private:
  glm::vec3 m_pos;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_world_up;

  glm::mat4 m_projection;

  f32 m_yaw;
  f32 m_pitch;
  f32 m_fov;

  f32 m_near = 0.001f;
  f32 m_far = 300.0f;

  void update_projection(u32 width, u32 height);
  void update_directions();
};

class Camera2D {
public:
  Camera2D(u32 width, u32 height,
           glm::vec2 pos = glm::vec2(0.0), f32 rotation = 0.0,
           glm::vec2 scale = glm::vec2(1.0));
  virtual ~Camera2D(){};

  glm::mat4 get_view_matrix();
  glm::mat4 get_projection_matrix();

  void update(u32 width, u32 height);
  void set_uniforms(gl::Shader &shader);

  void set_pos(glm::vec2 pos);
  glm::vec2 get_pos() const;

  void set_rot(f32 degrees);
  f32 get_rot() const;

  void set_scale(glm::vec2 scale);
  glm::vec2 get_scale() const;

private:
  void update_projection(u32 width, u32 height);

  f32 m_near = 0.0f;
  f32 m_far = 300.0f;

  glm::vec2 m_pos;
  f32 m_rotation;
  glm::vec2 m_scale;

  glm::mat4 m_projection;
};
} // namespace flex
