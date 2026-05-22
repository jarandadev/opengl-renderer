#pragma once

#include "RenderTypes.h"
#include <glm/glm.hpp>
#include <vector>

class Mesh;
class Material;

// Encapsulates a draw call request
struct RenderCommand {
  Mesh *mesh;
  Material *material;
  glm::mat4 worldMatrix;
};

// Represents light properties for the renderer
struct LightData {
  LightType type;
  glm::vec3 position;
  glm::vec3 color;
  float intensity;
};

// Container for all scene data required by the renderer per frame
struct RenderData {
  std::vector<RenderCommand> commands;
  std::vector<LightData> lights;
  glm::vec3 backgroundColor{0.0f};

  // Reset collections while keeping allocated capacity
  void clear() {
    commands.clear();
    lights.clear();
  }
};