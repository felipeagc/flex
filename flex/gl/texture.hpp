#pragma once

#include "gl.hpp"
#include <string>

namespace flex {
namespace gl {
enum TextureFilter { FILTER_NEAREST = GL_NEAREST, FILTER_LINEAR = GL_LINEAR };

class Texture {
public:
  Texture(TextureFilter filter = FILTER_LINEAR);
  ~Texture();

  void bind(GLuint unit = 0) const;
  static void unbind(GLuint unit = 0);

  GLuint get_id() const;
  const std::string &get_path() const;

  void load_from_file(const std::string &path);
  void load_from_data(void *data, unsigned int width, unsigned height,
                      GLenum format);

  void set_min_filter(TextureFilter filter);
  void set_mag_filter(TextureFilter filter);

private:
  GLuint m_id;
  std::string m_path;
};

} // namespace gl
} // namespace flex
