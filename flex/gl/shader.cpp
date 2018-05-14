#include "shader.hpp"

using namespace flex::gl;

Shader::Shader(const std::string &vertex_path,
               const std::string &fragment_path) {
  // Shader file loading

  std::string vertex_code;
  std::string fragment_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;
  // ensure ifstream objects can throw exceptions:
  v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    v_shader_file.open(FLEX_RES_PATH + vertex_path);
    f_shader_file.open(FLEX_RES_PATH + fragment_path);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << v_shader_file.rdbuf();
    fShaderStream << f_shader_file.rdbuf();
    // close file handlers
    v_shader_file.close();
    f_shader_file.close();
    // convert stream into string
    vertex_code = vShaderStream.str();
    fragment_code = fShaderStream.str();
  } catch (std::ifstream::failure &e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  const char *vertex_shader_source = vertex_code.c_str();
  const char *fragment_shader_source = fragment_code.c_str();

  // Shader compilation & linking

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  this->m_program = glCreateProgram();
  glAttachShader(m_program, vertex_shader);
  glAttachShader(m_program, fragment_shader);
  glLinkProgram(m_program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

Shader::~Shader() {
  glDeleteProgram(m_program);
}

void Shader::use() {
  glUseProgram(m_program);
}
