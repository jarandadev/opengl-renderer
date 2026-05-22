#pragma once

#include <chrono>

class Time {
  friend class Engine;

public:
  Time();

  // Timing getters
  float getDeltaTime() const { return m_deltaTime; }
  float getTotalTime() const { return m_totalTime; }
  float getFPS() const { return m_fps; }

private:
  std::chrono::steady_clock::time_point m_startTime;
  std::chrono::steady_clock::time_point m_lastFrameTime;

  float m_deltaTime = 0.0f;
  float m_totalTime = 0.0f;

  // FPS calculation state
  float m_fps = 0.0f;
  int m_fpsFrameCount = 0;
  float m_fpsAccumulatedTime = 0.0f;

  // Updates time metrics, called once per frame
  void tick();
};