#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace flex::gl;

Texture::Texture() { GL_CALL(glGenTextures(1, &m_id)); }

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

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }
}
