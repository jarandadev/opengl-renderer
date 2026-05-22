#include "SceneTree.h"

INode *SceneTree::findNode(const std::string &name) noexcept {
  return m_root.findNode(name);
}

void SceneTree::collect(RenderData &data) const {
  data.backgroundColor = m_backgroundColor;
  // Trigger recursive collection starting from identity matrix
  m_root.collect(data, glm::mat4{1.0f});
}

void SceneTree::RootNode::markDirty() noexcept {
  // Root doesn't track dirty state itself, but propagates to children
  for (auto &child : m_children) {
    child->markDirty();
  }
}

glm::mat4 SceneTree::RootNode::getWorldMatrix() const noexcept {
  // Root is always at the origin (identity matrix)
  return glm::mat4{1.0f};
}

void SceneTree::RootNode::collect(RenderData &data,
                                  const glm::mat4 &parentWorld) const {
  // Delegate to all children
  for (const auto &child : m_children) {
    child->collect(data, parentWorld);
  }
}