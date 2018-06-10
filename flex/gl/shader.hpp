#pragma once

#include "gl.hpp"
#include <flex/config.hpp>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace flex {
namespace gl {
class Shader {
public:
  Shader(const std::string &vertex_path, const std::string &fragment_path,
         std::map<std::string, std::string> options = {});
  ~Shader();

  void use() const;

  void set(const std::string &name, bool value);
  void set(const std::string &name, unsigned int value);
  void set(const std::string &name, float value);
  void set(const std::string &name, glm::vec3 value);
  void set(const std::string &name, glm::mat4 value);

private:
  GLuint m_program;

  bool check_compile_errors(GLuint shader, std::string type);
};
} // namespace gl
} // namespace flex
