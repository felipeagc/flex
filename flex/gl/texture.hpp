#pragma once

#include "../types.hpp"
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

  void bind(u32 unit = 0) const;
  static void unbind(u32 unit = 0);

  GLuint get_id() const;

  void load_from_file(const char *path);
  void load_from_data(void *data, u32 width, u32 height,
                      GLenum format);

  void set_min_filter(TextureFilter filter);
  void set_mag_filter(TextureFilter filter);

  i32 get_width();
  i32 get_height();

private:
  u32 m_id;
  i32 m_width = -1, m_height = -1;
};

} // namespace gl
} // namespace flex
