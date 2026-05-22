#pragma once

#include "Camera.h"
#include "Input.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Window.h"
#include "renderer/Renderer.h"
#include "scene/SceneTree.h"

#include <functional>
#include <string>

class Engine {
public:
  Engine(const std::string &title, int width = 1280, int height = 720);
  ~Engine();

  void run();
  void quit();

  void onUpdate(std::function<void()> callback);

  Input input;
  Time time;
  Window window;
  Camera camera;
  ResourceManager resources;
  SceneTree scene;

private:
  Renderer m_renderer;
  std::function<void()> m_updateCallback;

  void processDefaultCameraControls();
};