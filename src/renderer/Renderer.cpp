#include "Renderer.h"
#include "engine/Camera.h"
#include "renderer/Material.h"
#include "renderer/Mesh.h"
#include "renderer/Shader.h"
#include "scene/SceneTree.h"

#include <algorithm>
#include <array>
#include <glad/glad.h>

Renderer::Renderer() {
  // Pre-allocate space for common scene complexity
  m_frameData.commands.reserve(256);
  m_frameData.lights.reserve(8);
}

void Renderer::render(const SceneTree &scene, const Camera &camera) {
  glm::vec3 bg = scene.getBackgroundColor();
  glClearColor(bg.r, bg.g, bg.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reuse existing memory
  m_frameData.clear();
  m_frameData.backgroundColor = bg;
  scene.collect(m_frameData);

  if (m_frameData.commands.empty())
    return;

  std::sort(m_frameData.commands.begin(), m_frameData.commands.end(),
            [](const RenderCommand &a, const RenderCommand &b) {
              return a.material < b.material;
            });

  static const std::array<std::string, 8> lightNames = {
      "u_lights[0]", "u_lights[1]", "u_lights[2]", "u_lights[3]",
      "u_lights[4]", "u_lights[5]", "u_lights[6]", "u_lights[7]"};

  Material *activeMaterial = nullptr;
  Shader *activeShader = nullptr;

  for (const RenderCommand &cmd : m_frameData.commands) {
    if (cmd.material != activeMaterial) {
      activeMaterial = cmd.material;
      activeMaterial->bind();
      activeShader = activeMaterial->getShader();

      activeShader->setMat4("u_view", camera.getViewMatrix());
      activeShader->setMat4("u_projection", camera.getProjectionMatrix());
      activeShader->setVec3("u_viewPos", camera.getPosition());

      int numLights =
          static_cast<int>(std::min(m_frameData.lights.size(), size_t(8)));
      activeShader->setInt("u_numLights", numLights);

      for (int i = 0; i < numLights; ++i) {
        const LightData &l = m_frameData.lights[i];
        const std::string &base = lightNames[i];
        activeShader->setVec3(base + ".position", l.position);
        activeShader->setVec3(base + ".color", l.color);
        activeShader->setFloat(base + ".intensity", l.intensity);
        activeShader->setInt(base + ".type", static_cast<int>(l.type));
      }
    }

    activeShader->setMat4("u_model", cmd.worldMatrix);
    cmd.mesh->draw();
  }
}