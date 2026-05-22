#pragma once

#include <string>

class Texture {
public:
  Texture(const std::string &path, bool flipVertically);
  ~Texture();

  // Prevent copies; use references instead
  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;

  void bind(unsigned int slot = 0) const;

  unsigned int getId() const { return m_id; }

private:
  unsigned int m_id = 0;
};