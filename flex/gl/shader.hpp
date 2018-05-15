#pragma once

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>
#include <flex/config.hpp>
#include "util.hpp"

namespace flex {
namespace gl {
class Shader {
public:
  Shader(const std::string &vertex_path, const std::string &fragment_path);
  ~Shader();

  void use();

private:
  GLuint m_program;

  void check_compile_errors(GLuint shader, std::string type);
};
} // namespace gl
} // namespace flex
