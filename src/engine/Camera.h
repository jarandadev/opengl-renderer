#pragma once

#include <glm/glm.hpp>

enum class Direction { Forward, Backward, Left, Right, Up, Down };

class Camera {
  friend class Engine;

public:
  Camera();

  // Core Functionality
  glm::mat4 getViewMatrix() const;
  glm::mat4 getProjectionMatrix() const;

  void move(Direction direction, float deltaTime);
  void rotate(float xOffset, float yOffset);
  void zoom(float yOffset);

  // Setters
  void setPosition(const glm::vec3 &position) { m_position = position; }
  void setFov(float fov) { m_fov = fov; }
  void setMinFov(float minFov) { m_minFov = minFov; }
  void setMaxFov(float maxFov) { m_maxFov = maxFov; }
  void setSpeed(float speed) { m_speed = speed; }
  void setSensitivity(float sensitivity) { m_sensitivity = sensitivity; }
  void setNearPlane(float near) { m_near = near; }
  void setFarPlane(float far) { m_far = far; }
  void setDefaultControlsEnabled(bool enabled) {
    m_defaultControlsEnabled = enabled;
  }

  // Getters
  glm::vec3 getPosition() const { return m_position; }
  glm::vec3 getFront() const { return m_front; }
  float getFov() const { return m_fov; }
  float getMinFov() const { return m_minFov; }
  float getMaxFov() const { return m_maxFov; }
  float getSpeed() const { return m_speed; }
  float getSensitivity() const { return m_sensitivity; }
  float getAspectRatio() const { return m_aspectRatio; }
  float getNearPlane() const { return m_near; }
  float getFarPlane() const { return m_far; }
  bool areDefaultControlsEnabled() const { return m_defaultControlsEnabled; }

private:
  glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

  float m_yaw = -90.0f;
  float m_pitch = 0.0f;

  float m_minFov = 30.0f;
  float m_maxFov = 60.0f;
  float m_fov = 60.0f;
  float m_near = 0.1f;
  float m_far = 1000.0f;
  float m_aspectRatio = 1.7778f;

  float m_speed = 5.0f;
  float m_sensitivity = 0.1f;

  bool m_firstMouse = true;
  glm::vec2 m_lastMouse = glm::vec2(0.0f);
  bool m_defaultControlsEnabled = true;

  // Performance Caching
  mutable bool m_viewDirty = true;
  mutable bool m_projDirty = true;
  mutable glm::mat4 m_viewMatrix;
  mutable glm::mat4 m_projectionMatrix;

  // Internal Helper
  void updateOrientationVectors();

  // Called by Engine when window is resized
  void setAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;
    m_projDirty = true;
  }
};