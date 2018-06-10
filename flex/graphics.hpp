#pragma once

#include "drawable.hpp"
#include "filesystem.hpp"
#include "gl/shader.hpp"
#include <stack>

namespace flex {
enum ShaderType {
  SHADER_DEFAULT,
  SHADER_INSTANCED,
};

class GraphicsSystem {
private:
  std::stack<gl::Shader *> m_shader_stack;
  gl::Shader m_shader_default{path("shaders/simple.vert"),
                              path("shaders/simple.frag")};
  gl::Shader m_shader_default_instanced{path("shaders/simple.vert"),
                                        path("shaders/simple.frag"),
                                        {{"INSTANCED", "true"}}};

public:
  GraphicsSystem();
  ~GraphicsSystem();

  void push_shader(gl::Shader &shader);
  void pop_shader();

  // Returns the shader at the top of the stack.
  // If the stack is empty, return the default shader for
  // the specified shader type.
  gl::Shader *get_shader(ShaderType type = SHADER_DEFAULT);

  // Returns the default shader
  gl::Shader *get_shader_default();

  // Returns the default shader for instanced rendering
  gl::Shader *get_shader_default_instanced();

  void draw(Drawable &drawable, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0), glm::vec3 scale = glm::vec3(1.0));

  void draw_instanced(InstancedDrawable &drawable);
};
} // namespace flex
