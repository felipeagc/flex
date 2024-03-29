#include "texture.hpp"
#include <stb_image.h>

using namespace flex::gl;

Texture::Texture(TextureFilter filter) {
  GL_CALL(glGenTextures(1, &m_id));
  this->bind();

  auto mode = filter == FILTER_LINEAR ? GL_LINEAR : GL_NEAREST;
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode));
}

Texture::~Texture() {}

void Texture::destroy() { GL_CALL(glDeleteTextures(1, &m_id)); }

void Texture::bind(u32 unit) const {
  GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::unbind(u32 unit) {
  GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

GLuint Texture::get_id() const { return m_id; }

void Texture::load_from_file(const char *path) {
  i32 n_components;
  stbi_set_flip_vertically_on_load(true);
  u8 *data =
      stbi_load(path, &m_width, &m_height, &n_components, 0);
  if (data) {
    GLenum format = GL_RGB;
    if (n_components == 1)
      format = GL_RED;
    else if (n_components == 3)
      format = GL_RGB;
    else if (n_components == 4)
      format = GL_RGBA;

    this->bind();

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format,
                         GL_UNSIGNED_BYTE, data));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

    flex::log(L_DEBUG, L_IMPORT, "Texture loaded: %s", path);

    stbi_image_free(data);
  } else {
    flex::log(L_ERROR, L_IMPORT, "Texture failed to load at path: %s", path);
    stbi_image_free(data);
  }
  stbi_set_flip_vertically_on_load(false);
}

void Texture::load_from_data(void *data, unsigned int width,
                             u32 height, GLenum format) {
  m_width = width;
  m_height = height;
  this->bind();
  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                       GL_UNSIGNED_BYTE, data));

  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

  GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

  flex::log(L_DEBUG, L_IMPORT, "Texture loaded from data");
}

void Texture::set_min_filter(TextureFilter filter) {
  this->bind();
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter));
}

void Texture::set_mag_filter(TextureFilter filter) {
  this->bind();
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter));
}

i32 Texture::get_width() {
  return m_width;
}

i32 Texture::get_height() {
  return m_height;
}
