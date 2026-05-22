#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

static float calculateAspectRatio(int width, int height) {
  return static_cast<float>(width) / static_cast<float>(height);
}

Window::Window(const std::string &title, int width, int height)
    : m_width(width), m_height(height),
      m_aspectRatio(calculateAspectRatio(width, height)) {

  // Initialize OpenGL context
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  m_window =
      glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr);
  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1); // Enable VSync

  // Bind instance to window for callback access
  glfwSetWindowUserPointer(m_window, this);

  // Register GLFW callbacks
  glfwSetScrollCallback(m_window, scrollCallback);
  glfwSetCursorPosCallback(m_window, cursorPosCallback);
  glfwSetKeyCallback(m_window, keyCallback);
  glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
}

Window::~Window() {
  if (m_window)
    glfwDestroyWindow(m_window);
}

void Window::close() { glfwSetWindowShouldClose(m_window, true); }

bool Window::shouldClose() const { return glfwWindowShouldClose(m_window); }

void Window::swapBuffers() const { glfwSwapBuffers(m_window); }

void Window::captureCursor() const {
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::freeCursor() const {
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::setCallbacks(WindowCallbacks callbacks) {
  m_callbacks = std::move(callbacks);
}

// Callback dispatchers
void Window::scrollCallback(GLFWwindow *window, double x, double y) {
  auto *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (w && w->m_callbacks.onScroll)
    w->m_callbacks.onScroll(static_cast<float>(y));
}

void Window::cursorPosCallback(GLFWwindow *window, double x, double y) {
  auto *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (w && w->m_callbacks.onCursorPos)
    w->m_callbacks.onCursorPos(static_cast<float>(x), static_cast<float>(y));
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  auto *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (w && w->m_callbacks.onKey)
    w->m_callbacks.onKey(key, action);
}

void Window::framebufferResizeCallback(GLFWwindow *window, int width,
                                       int height) {
  auto *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (w && height > 0) {
    w->m_width = width;
    w->m_height = height;
    w->m_aspectRatio = calculateAspectRatio(width, height);

    if (w->m_callbacks.onFramebufferResize)
      w->m_callbacks.onFramebufferResize(width, height, w->m_aspectRatio);
  }
}