#include "Texture.h"

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <stdexcept>

Texture::Texture(const std::string &path, bool flipVertically) {
  stbi_set_flip_vertically_on_load(flipVertically);

  int w, h, channels;
  unsigned char *data = stbi_load(path.c_str(), &w, &h, &channels, 0);
  if (!data)
    throw std::runtime_error("Texture: failed to load " + path);

  GLenum fmt = (channels == 4) ? GL_RGBA : GL_RGB;

  glGenTextures(1, &m_id);
  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexImage2D(GL_TEXTURE_2D, 0, fmt, w, h, 0, fmt, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Set texture wrapping and filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_image_free(data);
}

Texture::~Texture() {
  if (m_id)
    glDeleteTextures(1, &m_id);
}

void Texture::bind(unsigned int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_id);
}