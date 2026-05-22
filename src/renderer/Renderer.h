#pragma once

#include "RenderData.h"
#include "engine/Camera.h"
#include "scene/SceneTree.h"

class Renderer {
public:
  Renderer();
  void render(const SceneTree &scene, const Camera &camera);

private:
  RenderData m_frameData;
};