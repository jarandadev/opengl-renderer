#pragma once

#include <glm/glm.hpp>

class Shader;
class Texture;

class Material {
public:
  Material(Shader &shader);

  // Prevent copies; use references instead
  Material(const Material &) = delete;
  Material &operator=(const Material &) = delete;

  // Fluent API for material configuration
  Material &setDiffuseTexture(Texture &tex);
  Material &setSpecularTexture(Texture &tex);
  Material &setShininess(float value);
  Material &setColor(const glm::vec3 &color);

  Shader *getShader() const { return m_shader; }

  // Applies shader and binds textures
  void bind() const;

private:
  Shader *m_shader = nullptr;
  Texture *m_diffuse = nullptr;
  Texture *m_specular = nullptr;
  float m_shininess = 64.0f;
  glm::vec3 m_color = {0.0f, 1.0f, 0.0f};
};