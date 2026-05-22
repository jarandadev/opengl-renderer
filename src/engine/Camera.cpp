#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() { updateOrientationVectors(); }

glm::mat4 Camera::getViewMatrix() const {
  if (m_viewDirty) {
    m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
    m_viewDirty = false;
  }
  return m_viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
  if (m_projDirty) {
    m_projectionMatrix =
        glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
    m_projDirty = false;
  }
  return m_projectionMatrix;
}

void Camera::move(Direction direction, float deltaTime) {
  float distance = m_speed * deltaTime;

  glm::vec3 right =
      glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
  glm::vec3 flatFront = glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z));

  switch (direction) {
  case Direction::Forward:
    m_position += distance * flatFront;
    break;
  case Direction::Backward:
    m_position -= distance * flatFront;
    break;
  case Direction::Left:
    m_position -= distance * right;
    break;
  case Direction::Right:
    m_position += distance * right;
    break;
  case Direction::Up:
    m_position.y += distance;
    break;
  case Direction::Down:
    m_position.y -= distance;
    break;
  }

  m_viewDirty = true;
}

void Camera::rotate(float xOffset, float yOffset) {
  m_yaw += xOffset * m_sensitivity;
  m_pitch = glm::clamp(m_pitch + (yOffset * m_sensitivity), -89.0f, 89.0f);

  updateOrientationVectors();
  m_viewDirty = true;
}

void Camera::zoom(float yOffset) {
  m_fov = glm::clamp(m_fov - yOffset, m_minFov, m_maxFov);
  m_projDirty = true;
}

void Camera::updateOrientationVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front = glm::normalize(front);

  glm::vec3 right =
      glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
  m_up = glm::normalize(glm::cross(right, m_front));
}