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

  void destroy();

  void bind(GLuint unit = 0) const;
  static void unbind(GLuint unit = 0);

  GLuint get_id() const;

  void load_from_file(const char* path);
  void load_from_data(void *data, unsigned int width, unsigned height,
                      GLenum format);

  void set_min_filter(TextureFilter filter);
  void set_mag_filter(TextureFilter filter);

  int get_width();
  int get_height();

private:
  GLuint m_id;
  int m_width = -1, m_height = -1;
};

} // namespace gl
} // namespace flex
