#include "MeshNode.h"
#include "renderer/Material.h"
#include "renderer/Mesh.h"

MeshNode &MeshNode::setMesh(Mesh &mesh) {
  m_mesh = &mesh;
  return *this;
}

MeshNode &MeshNode::setMaterial(Material &material) {
  m_material = &material;
  return *this;
}

void MeshNode::collect(RenderData &data, const glm::mat4 &parentWorld) const {
  glm::mat4 world = parentWorld * getLocalMatrix();

  if (m_mesh && m_material)
    data.commands.push_back({m_mesh, m_material, world});

  collectChildren(data, world);
}