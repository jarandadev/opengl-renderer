#include "Sylph.h"

int main() {
  Engine engine("Usage Example");

  // Setup scene
  engine.scene.setBackgroundColor({0.05f, 0.05f, 0.05f});
  engine.camera.setPosition({0.0f, 0.0f, 0.0f});

  // Load resources
  Mesh &sphereMesh = engine.resources.loadMesh(Primitive::Sphere);

  Shader &litShader = engine.resources.loadShader("assets/shaders/lit.vert",
                                                  "assets/shaders/lit.frag");
  Shader &basicShader = engine.resources.loadShader(
      "assets/shaders/basic.vert", "assets/shaders/basic.frag");

  Texture &diffuse =
      engine.resources.loadTexture("assets/textures/container.png");
  Texture &specular =
      engine.resources.loadTexture("assets/textures/container_specular.png");

  // Create materials
  Material &boxMat = engine.resources.createMaterial("box", litShader)
                         .setDiffuseTexture(diffuse)
                         .setSpecularTexture(specular)
                         .setShininess(0.5f);

  Material &lightMat = engine.resources.createMaterial("light", basicShader)
                           .setColor({0.9f, 0.6f, 0.4f});

  // Build scene
  MeshNode &box = engine.scene.createNode<MeshNode>("box")
                      .setMesh(sphereMesh)
                      .setMaterial(boxMat)
                      .setPosition({0.0f, 0.0f, -3.0f});

  MeshNode &lightSource = engine.scene.createNode<MeshNode>("light")
                              .setMesh(sphereMesh)
                              .setMaterial(lightMat)
                              .setScale({0.5f, 0.5f, 0.5f})
                              .setPosition({2.0f, 2.0f, -1.0f});

  lightSource.createChild<LightNode>("lightNode")
      .setIntensity(3.0f)
      .setColor({0.9f, 0.6f, 0.4f});

  // Game loop
  engine.onUpdate([&]() {
    if (engine.input.isKeyJustPressed(Key::Escape))
      engine.quit();

    box.rotate(engine.time.getDeltaTime() * 45.0f, {1.0f, 1.0f, 1.0f});
  });

  engine.run();
}