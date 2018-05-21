#pragma once

#include <flex/gl/util.hpp>
#include <glad/glad.h>
#include <string>

namespace flex {
namespace gl {
class Texture {
public:
  Texture();
  ~Texture();

  void bind(GLuint unit = 0) const;
  static void unbind();

  GLuint get_id() const;
  const std::string &get_path() const;

  void load_from_file(const std::string& path);

private:
  GLuint m_id;
  std::string m_path;
};
} // namespace gl
} // namespace flex
