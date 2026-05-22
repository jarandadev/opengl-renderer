#pragma once

#include <functional>
#include <string>

struct GLFWwindow;

// Defines callbacks for input and window events
struct WindowCallbacks {
  std::function<void(float)> onScroll;
  std::function<void(float, float)> onCursorPos;
  std::function<void(int, int)> onKey;
  std::function<void(int, int, float)> onFramebufferResize;
};

class Window {
  friend class Engine;

public:
  Window(const std::string &title, int width = 1280, int height = 720);
  ~Window();

  void captureCursor() const;
  void freeCursor() const;

  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }
  float getAspectRatio() const { return m_aspectRatio; }

private:
  GLFWwindow *m_window = nullptr;
  int m_width;
  int m_height;
  float m_aspectRatio;
  WindowCallbacks m_callbacks;

  void swapBuffers() const;
  void setCallbacks(WindowCallbacks callbacks);
  bool shouldClose() const;
  void close();

  GLFWwindow *getGLFWwindow() const { return m_window; }

  // Static GLFW event dispatchers
  static void framebufferResizeCallback(GLFWwindow *window, int width,
                                        int height);
  static void scrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);
  static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
};