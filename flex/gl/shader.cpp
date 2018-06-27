#include "shader.hpp"

using namespace flex::gl;

Shader::Shader(const std::string &vertex_path, const std::string &fragment_path,
               std::map<std::string, std::string> options) {
  // Shader file loading
  std::string defines;
  for (auto &pair : options) {
    defines += "#define " + pair.first + " " + pair.second + "\n";
  }

  std::string vertex_code;
  std::string fragment_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;
  // ensure ifstream objects can throw exceptions:
  v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    v_shader_file.open(vertex_path);
    f_shader_file.open(fragment_path);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << v_shader_file.rdbuf();
    fShaderStream << f_shader_file.rdbuf();
    // close file handlers
    v_shader_file.close();
    f_shader_file.close();
    // convert stream into string
    vertex_code = vShaderStream.str();
    vertex_code =
        vertex_code.substr(0, vertex_code.find("\n")) + "\n" + defines +
        vertex_code.substr(vertex_code.find("\n"), vertex_code.size());
    fragment_code = fShaderStream.str();
    fragment_code =
        fragment_code.substr(0, fragment_code.find("\n")) + "\n" + defines +
        fragment_code.substr(fragment_code.find("\n"), fragment_code.size());
  } catch (std::ifstream::failure &e) {
    flex::log(L_ERROR, L_GL, "Error: Shader file not succesfully read");
  }

  const char *vertex_shader_source = vertex_code.c_str();
  const char *fragment_shader_source = fragment_code.c_str();

  // Shader compilation & linking
  bool success = true;

  GL_CALL(GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER));
  GL_CALL(glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL));
  GL_CALL(glCompileShader(vertex_shader));
  success = success && check_compile_errors(vertex_shader, "VERTEX");

  GL_CALL(GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER));
  GL_CALL(glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL));
  GL_CALL(glCompileShader(fragment_shader));
  success = success && check_compile_errors(fragment_shader, "FRAGMENT");

  GL_CALL(this->m_program = glCreateProgram());
  GL_CALL(glAttachShader(m_program, vertex_shader));
  GL_CALL(glAttachShader(m_program, fragment_shader));
  GL_CALL(glLinkProgram(m_program));
  success = success && check_compile_errors(m_program, "PROGRAM");

  if (success) {
    flex::log(L_DEBUG, L_GL, "Loaded shader program: '%s', '%s'",
              vertex_path.c_str(), fragment_path.c_str());
  }

  GL_CALL(glDeleteShader(vertex_shader));
  GL_CALL(glDeleteShader(fragment_shader));
}

Shader::~Shader() { GL_CALL(glDeleteProgram(m_program)); }

void Shader::use() const { GL_CALL(glUseProgram(m_program)); }

bool Shader::check_compile_errors(GLuint shader, std::string type) {
  int success;
  char info_log[1024];
  if (type != "PROGRAM") {
    GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
      GL_CALL(glGetShaderInfoLog(shader, 1024, NULL, info_log));
      flex::log(L_ERROR, L_GL,
                "Error: Shader compilation error of type: %s/n%s", type.c_str(),
                info_log);
    }
  } else {
    GL_CALL(glGetProgramiv(shader, GL_LINK_STATUS, &success));
    if (!success) {
      GL_CALL(glGetProgramInfoLog(shader, 1024, NULL, info_log));
      flex::log(L_ERROR, L_GL,
                "Error: Shader program linking error of type: %s/n%s", type.c_str(),
                info_log);
    }
  }

  return (success ? true : false);
}

void Shader::set(const std::string &name, bool value) {
  this->use();
  GL_CALL(GLint location = glGetUniformLocation(m_program, name.c_str()));
  GL_CALL(glUniform1i(location, value));
}

void Shader::set(const std::string &name, unsigned int value) {
  this->use();
  GL_CALL(GLint location = glGetUniformLocation(m_program, name.c_str()));
  GL_CALL(glUniform1i(location, value));
}

void Shader::set(const std::string &name, float value) {
  this->use();
  GL_CALL(GLint location = glGetUniformLocation(m_program, name.c_str()));
  GL_CALL(glUniform1f(location, value));
}

void Shader::set(const std::string &name, glm::vec3 value) {
  this->use();
  GL_CALL(GLint location = glGetUniformLocation(m_program, name.c_str()));
  GL_CALL(glUniform3fv(location, 1, glm::value_ptr(value)));
}

void Shader::set(const std::string &name, glm::mat4 value) {
  this->use();
  GL_CALL(GLint location = glGetUniformLocation(m_program, name.c_str()));
  GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
}
