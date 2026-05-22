#include "Engine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

static void InitGLFWOrThrow() {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }
}

Engine::Engine(const std::string &title, int width, int height)
    : window((InitGLFWOrThrow(), Window(title, width, height))) {

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  // Configure global OpenGL state
  glEnable(GL_DEPTH_TEST);

  camera.setAspectRatio(window.getAspectRatio());

  window.setCallbacks({
      .onScroll = [this](float delta) { 
          input.setScrollDelta(delta); 
      },
      .onCursorPos = [this](float x, float y) { 
          input.setCursorPosition(x, y); 
      },
      .onKey = [this](int key, int action) { 
          input.processKeyEvent(key, action); 
      },
      .onFramebufferResize = [this](int, int, float aspect) { 
          camera.setAspectRatio(aspect); 
      }
  });
}

Engine::~Engine() { glfwTerminate(); }

void Engine::run() {
  window.captureCursor();

  while (!window.shouldClose()) {
    // 1. Input & Time
    time.tick();
    glfwPollEvents();
    processDefaultCameraControls();

    // 2. Logic
    if (m_updateCallback)
      m_updateCallback();

    // 3. Render
    m_renderer.render(scene, camera);
    window.swapBuffers();

    // 4. Cleanup
    input.endFrame();
  }
}

void Engine::processDefaultCameraControls() {
  if (!camera.areDefaultControlsEnabled())
    return;

  float dt = time.getDeltaTime();

  if (input.isKeyPressed(Key::W))
    camera.move(Direction::Forward, dt);
  if (input.isKeyPressed(Key::S))
    camera.move(Direction::Backward, dt);
  if (input.isKeyPressed(Key::A))
    camera.move(Direction::Left, dt);
  if (input.isKeyPressed(Key::D))
    camera.move(Direction::Right, dt);
  if (input.isKeyPressed(Key::Space))
    camera.move(Direction::Up, dt);
  if (input.isKeyPressed(Key::LeftShift))
    camera.move(Direction::Down, dt);

  float xDelta = input.getMouseXDelta();
  float yDelta = input.getMouseYDelta();

  if (glm::abs(xDelta) > 0.0001f || glm::abs(yDelta) > 0.0001f) {
    camera.rotate(xDelta, -yDelta);
  }
}

void Engine::onUpdate(std::function<void()> callback) {
  m_updateCallback = std::move(callback);
}

void Engine::quit() { window.close(); }