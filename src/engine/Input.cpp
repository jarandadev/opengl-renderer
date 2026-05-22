#include "Input.h"
#include <GLFW/glfw3.h>

// Translates internal Key enum to GLFW specific codes
static int ToGlfwKey(Key key) {
  switch (key) {
  case Key::W:
    return GLFW_KEY_W;
  case Key::S:
    return GLFW_KEY_S;
  case Key::A:
    return GLFW_KEY_A;
  case Key::D:
    return GLFW_KEY_D;
  case Key::Space:
    return GLFW_KEY_SPACE;
  case Key::LeftShift:
    return GLFW_KEY_LEFT_SHIFT;
  case Key::Tab:
    return GLFW_KEY_TAB;
  case Key::Escape:
    return GLFW_KEY_ESCAPE;
  case Key::F:
    return GLFW_KEY_F;
  }
  return GLFW_KEY_UNKNOWN;
}

bool Input::isKeyPressed(Key key) const {
  int glfwKey = ToGlfwKey(key);
  auto it = m_keys.find(glfwKey);
  if (it != m_keys.end()) {
    return it->second == GLFW_PRESS || it->second == GLFW_REPEAT;
  }
  return false;
}

bool Input::isKeyJustPressed(Key key) const {
  int glfwKey = ToGlfwKey(key);
  auto curr = m_keys.find(glfwKey);
  auto prev = m_prevKeys.find(glfwKey);

  bool currentlyPressed = curr != m_keys.end() && (curr->second == GLFW_PRESS ||
                                                   curr->second == GLFW_REPEAT);
  bool previouslyPressed =
      prev != m_prevKeys.end() &&
      (prev->second == GLFW_PRESS || prev->second == GLFW_REPEAT);

  return currentlyPressed && !previouslyPressed;
}

bool Input::isKeyJustReleased(Key key) const {
  int glfwKey = ToGlfwKey(key);
  auto curr = m_keys.find(glfwKey);
  auto prev = m_prevKeys.find(glfwKey);

  bool currentlyPressed = curr != m_keys.end() && (curr->second == GLFW_PRESS ||
                                                   curr->second == GLFW_REPEAT);
  bool previouslyPressed =
      prev != m_prevKeys.end() &&
      (prev->second == GLFW_PRESS || prev->second == GLFW_REPEAT);

  return !currentlyPressed && previouslyPressed;
}

void Input::processKeyEvent(int key, int action) { m_keys[key] = action; }

void Input::setCursorPosition(float x, float y) {
  m_mousePosition.x = x;
  m_mousePosition.y = y;

  // Prevent camera jump on first frame
  if (m_firstMouse) {
    m_lastMousePosition = m_mousePosition;
    m_firstMouse = false;
    return;
  }

  m_mouseDelta.x += m_mousePosition.x - m_lastMousePosition.x;
  m_mouseDelta.y += m_mousePosition.y - m_lastMousePosition.y;

  m_lastMousePosition = m_mousePosition;
}

void Input::setScrollDelta(float delta) { m_scrollDelta = delta; }

void Input::endFrame() {
  // Reset frame-specific input data
  m_scrollDelta = 0.0f;
  m_mouseDelta = glm::vec2(0.0f);

  // Update state for next frame's "JustPressed" detection
  m_prevKeys = m_keys;
}