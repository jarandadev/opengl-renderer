#pragma once

#include "INode.h"

#include <glm/gtc/matrix_transform.hpp>
#include <string>

template <typename Derived> class Node : public INode {
public:
  explicit Node(const std::string &name) : m_name(name) {}

  // Fluent API setters
  Derived &setPosition(const glm::vec3 &v) noexcept {
    m_position = v;
    markDirty();
    return derived();
  }
  Derived &setRotation(const glm::vec3 &v) noexcept {
    m_rotation = v;
    markDirty();
    return derived();
  }
  Derived &setScale(const glm::vec3 &v) noexcept {
    m_scale = v;
    markDirty();
    return derived();
  }

  Derived &rotate(float angleDeg, const glm::vec3 &axis) noexcept {
    m_rotation += axis * angleDeg;
    markDirty();
    return derived();
  }

  // Getters
  [[nodiscard]] std::string getName() const noexcept override { return m_name; }
  [[nodiscard]] glm::vec3 getPosition() const noexcept { return m_position; }
  [[nodiscard]] glm::vec3 getRotation() const noexcept { return m_rotation; }
  [[nodiscard]] glm::vec3 getScale() const noexcept { return m_scale; }

  // Transform calculations
  [[nodiscard]] glm::mat4 getLocalMatrix() const noexcept;
  [[nodiscard]] glm::mat4 getWorldMatrix() const noexcept override;
  void collect(RenderData &data,
               const glm::mat4 &parentWorld) const override = 0;

  // Implementation of polymorphic dirty-flag propagation
  void markDirty() noexcept override {
    if (m_dirty)
      return;
    m_dirty = true;
    for (auto &child : m_children)
      child->markDirty();
  }

protected:
  void collectChildren(RenderData &data, const glm::mat4 &world) const;

private:
  std::string m_name;
  glm::vec3 m_position{0.0f}, m_rotation{0.0f}, m_scale{1.0f};

  mutable bool m_dirty = true;
  mutable glm::mat4 m_cachedWorldMatrix{1.0f};

  Derived &derived() noexcept { return static_cast<Derived &>(*this); }
};

// Template implementation
template <typename Derived>
glm::mat4 Node<Derived>::getLocalMatrix() const noexcept {
  glm::mat4 m{1.0f};
  m = glm::translate(m, m_position);
  m = glm::rotate(m, glm::radians(m_rotation.x), {1, 0, 0});
  m = glm::rotate(m, glm::radians(m_rotation.y), {0, 1, 0});
  m = glm::rotate(m, glm::radians(m_rotation.z), {0, 0, 1});
  m = glm::scale(m, m_scale);
  return m;
}

template <typename Derived>
glm::mat4 Node<Derived>::getWorldMatrix() const noexcept {
  if (m_dirty) {
    glm::mat4 parent = m_parent ? m_parent->getWorldMatrix() : glm::mat4{1.0f};
    m_cachedWorldMatrix = parent * getLocalMatrix();
    m_dirty = false;
  }
  return m_cachedWorldMatrix;
}

template <typename Derived>
void Node<Derived>::collectChildren(RenderData &data,
                                    const glm::mat4 &world) const {
  for (const auto &child : m_children)
    child->collect(data, world);
}