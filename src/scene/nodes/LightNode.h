#pragma once

#include "renderer/RenderTypes.h"
#include "scene/Node.h"

class LightNode : public Node<LightNode> {
public:
  explicit LightNode(const std::string &name) : Node<LightNode>(name) {}

  // Fluent API setters
  LightNode &setType(LightType type);
  LightNode &setColor(const glm::vec3 &color);
  LightNode &setIntensity(float intensity);

  // Adds light data to the render command queue
  void collect(RenderData &data, const glm::mat4 &parentWorld) const override;

private:
  LightType m_type = LightType::Point;
  glm::vec3 m_color{1.0f};
  float m_intensity = 1.0f;
};