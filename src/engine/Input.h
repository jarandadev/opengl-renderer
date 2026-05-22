#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

enum class Key { W, S, A, D, Space, LeftShift, Tab, Escape, F };

class Input {
  friend class Engine;

public:
  // Key state queries
  bool isKeyPressed(Key key) const;
  bool isKeyJustPressed(Key key) const;
  bool isKeyJustReleased(Key key) const;

  // Mouse and scroll getters
  glm::vec2 getMousePosition() const { return m_mousePosition; }
  float getScrollDelta() const { return m_scrollDelta; }
  float getMouseXDelta() const { return m_mouseDelta.x; }
  float getMouseYDelta() const { return m_mouseDelta.y; }

private:
  // Key state tracking
  std::unordered_map<int, int> m_keys;
  std::unordered_map<int, int> m_prevKeys;

  // Mouse state tracking
  glm::vec2 m_mousePosition = glm::vec2(0.0f);
  glm::vec2 m_lastMousePosition = glm::vec2(0.0f);
  glm::vec2 m_mouseDelta = glm::vec2(0.0f);

  float m_scrollDelta = 0.0f;
  bool m_firstMouse = true;

  // Called by Engine via window callbacks
  void processKeyEvent(int key, int action);
  void setCursorPosition(float x, float y);
  void setScrollDelta(float delta);

  // Resets frame-specific input
  void endFrame();
};