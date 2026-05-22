#include "Material.h"
#include "Shader.h"
#include "Texture.h"

Material::Material(Shader &shader) : m_shader(&shader) {}

Material &Material::setDiffuseTexture(Texture &tex) {
  m_diffuse = &tex;
  return *this;
}

Material &Material::setSpecularTexture(Texture &tex) {
  m_specular = &tex;
  return *this;
}

Material &Material::setShininess(float value) {
  m_shininess = value;
  return *this;
}

Material &Material::setColor(const glm::vec3 &color) {
  m_color = color;
  return *this;
}

void Material::bind() const {
  m_shader->use();

  // Handle diffuse properties
  bool hasDiffuse = m_diffuse != nullptr;
  m_shader->setBool("u_hasDiffuse", hasDiffuse);
  if (hasDiffuse) {
    m_diffuse->bind(0);
    m_shader->setInt("u_diffuse", 0);
  } else {
    m_shader->setVec3("u_color", m_color);
  }

  // Handle specular properties
  bool hasSpecular = m_specular != nullptr;
  m_shader->setBool("u_hasSpecular", hasSpecular);
  if (hasSpecular) {
    m_specular->bind(1);
    m_shader->setInt("u_specular", 1);
  }

  m_shader->setFloat("u_shininess", m_shininess);
}