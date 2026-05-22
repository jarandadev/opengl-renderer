#pragma once

#include "renderer/RenderData.h"

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

class INode {
public:
  virtual ~INode() = default;

  // Prevent copies; use references instead
  INode(const INode &) = delete;
  INode &operator=(const INode &) = delete;

  [[nodiscard]] virtual std::string getName() const noexcept = 0;

  // Dirty-flag propagation and matrix calculation interface
  virtual void markDirty() noexcept = 0;
  virtual glm::mat4 getWorldMatrix() const noexcept = 0;

  virtual void collect(RenderData &data,
                       const glm::mat4 &parentWorld) const = 0;

  INode *findNode(const std::string &name) noexcept {
    if (getName() == name)
      return this;
    for (auto &child : m_children)
      if (auto *found = child->findNode(name))
        return found;
    return nullptr;
  }

  // Create and attach a new child node
  template <typename T, typename... Args>
  T &createChild(const std::string &name, Args &&...args) {
    auto node = std::make_unique<T>(name, std::forward<Args>(args)...);
    T &ref = *node;
    node->m_parent = this;
    m_children.push_back(std::move(node));
    return ref;
  }

protected:
  explicit INode() = default;

  INode *m_parent = nullptr;
  std::vector<std::unique_ptr<INode>> m_children;
};