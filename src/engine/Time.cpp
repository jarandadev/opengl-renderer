#include "Time.h"

Time::Time()
    : m_startTime(std::chrono::steady_clock::now()),
      m_lastFrameTime(std::chrono::steady_clock::now()) {}

void Time::tick() {
  auto currentFrameTime = std::chrono::steady_clock::now();

  // Calculate delta time since last frame
  std::chrono::duration<float> elapsed = currentFrameTime - m_lastFrameTime;
  m_deltaTime = elapsed.count();

  // Update total engine running time
  std::chrono::duration<float> total = currentFrameTime - m_startTime;
  m_totalTime = total.count();

  m_lastFrameTime = currentFrameTime;

  // Update FPS every second
  m_fpsFrameCount++;
  m_fpsAccumulatedTime += m_deltaTime;

  if (m_fpsAccumulatedTime >= 1.0f) {
    m_fps = static_cast<float>(m_fpsFrameCount) / m_fpsAccumulatedTime;
    m_fpsFrameCount = 0;
    m_fpsAccumulatedTime = 0.0f;
  }
}