#pragma once

#include "INode.h"
#include "renderer/RenderData.h"

#include <glm/glm.hpp>
#include <string>

class SceneTree {
public:
  // Creates and adds a node to the root of the tree
  template <typename T, typename... Args>
  T &createNode(const std::string &name, Args &&...args) {
    return m_root.createChild<T>(name, std::forward<Args>(args)...);
  }

  INode *findNode(const std::string &name) noexcept;

  // Background color configuration
  void setBackgroundColor(const glm::vec3 &color) noexcept {
    m_backgroundColor = color;
  }
  [[nodiscard]] glm::vec3 getBackgroundColor() const noexcept {
    return m_backgroundColor;
  }

  // Gathers render data for the renderer
  void collect(RenderData &data) const;

private:
  // Internal container for the node hierarchy
  class RootNode : public INode {
  public:
    RootNode() = default;

    [[nodiscard]] std::string getName() const noexcept override {
      return "__root__";
    }

    void markDirty() noexcept override;

    [[nodiscard]] glm::mat4 getWorldMatrix() const noexcept override;

    void collect(RenderData &data, const glm::mat4 &parentWorld) const override;
  };

  RootNode m_root;
  glm::vec3 m_backgroundColor{0.0f};
};