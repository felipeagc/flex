#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

using namespace flex::gl;

Texture::Texture(TextureFilter filter) {
  GL_CALL(glGenTextures(1, &m_id));
  this->bind();

  auto mode = filter == FILTER_LINEAR ? GL_LINEAR : GL_NEAREST;
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode));
}

Texture::~Texture() { GL_CALL(glDeleteTextures(1, &m_id)); }

void Texture::bind(GLuint unit) const {
  GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::unbind(GLuint unit) {
  GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

GLuint Texture::get_id() const { return m_id; }

const std::string &Texture::get_path() const { return m_path; }

void Texture::load_from_file(const std::string &path) {
  m_path = path;

  int width, height, n_components;
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &n_components, 0);
  if (data) {
    GLenum format = GL_RGB;
    if (n_components == 1)
      format = GL_RED;
    else if (n_components == 3)
      format = GL_RGB;
    else if (n_components == 4)
      format = GL_RGBA;

    this->bind();

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                         GL_UNSIGNED_BYTE, data));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

    flex::log(L_DEBUG, L_IMPORT, "Texture loaded: " + path);

    stbi_image_free(data);
  } else {
    flex::log(L_ERROR, L_IMPORT, "Texture failed to load at path: " + path);
    stbi_image_free(data);
  }
}

void Texture::load_from_data(void *data, unsigned int width,
                             unsigned int height) {
  this->bind();
  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                       GL_UNSIGNED_BYTE, data));

  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

  GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

  flex::log(L_DEBUG, L_IMPORT, "Texture loaded from data");
}

void Texture::set_filter(TextureFilter filter) {
  this->bind();
  auto mode = filter == FILTER_LINEAR ? GL_LINEAR : GL_NEAREST;
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode));
}
