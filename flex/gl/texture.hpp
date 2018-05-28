#pragma once

#include "gl.hpp"
#include <string>

namespace flex {
namespace gl {
enum TextureFilter { FILTER_NEAREST, FILTER_LINEAR };

class Texture {
public:
  Texture(TextureFilter filter = FILTER_LINEAR);
  ~Texture();

  void bind(GLuint unit = 0) const;
  static void unbind(GLuint unit = 0);

  GLuint get_id() const;
  const std::string &get_path() const;

  void load_from_file(const std::string &path);
  void load_from_data(void *data, unsigned int width, unsigned height);

  void set_filter(TextureFilter filter);

private:
  GLuint m_id;
  std::string m_path;
};

} // namespace gl
} // namespace flex
