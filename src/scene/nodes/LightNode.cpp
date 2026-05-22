#include "LightNode.h"

LightNode &LightNode::setType(LightType type) {
  m_type = type;
  return *this;
}

LightNode &LightNode::setColor(const glm::vec3 &color) {
  m_color = color;
  return *this;
}

LightNode &LightNode::setIntensity(float intensity) {
  m_intensity = intensity;
  return *this;
}

void LightNode::collect(RenderData &data, const glm::mat4 &parentWorld) const {
  glm::mat4 world = parentWorld * getLocalMatrix();

  // Extract light position from world matrix translation column
  LightData ld;
  ld.type = m_type;
  ld.color = m_color;
  ld.intensity = m_intensity;
  ld.position = glm::vec3(world[3]);

  data.lights.push_back(ld);

  collectChildren(data, world);
}