#pragma once

#include "scene/Node.h"

class Mesh;
class Material;

class MeshNode : public Node<MeshNode> {
public:
  explicit MeshNode(const std::string &name) : Node<MeshNode>(name) {}

  // Fluent API setters
  MeshNode &setMesh(Mesh &mesh);
  MeshNode &setMaterial(Material &material);

  Mesh *getMesh() const { return m_mesh; }
  Material *getMaterial() const { return m_material; }

  // Adds mesh data to the render command queue
  void collect(RenderData &data, const glm::mat4 &parentWorld) const override;

private:
  Mesh *m_mesh = nullptr;
  Material *m_material = nullptr;
};