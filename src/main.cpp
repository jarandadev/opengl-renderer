#include "Sylph.h"

int main() {
  Engine engine("Solar System");

  engine.scene.setBackgroundColor({0.0f, 0.0f, 0.0f});
  engine.camera.setPosition({0.0f, 0.0f, 0.0f});

  // Resources
  Mesh &sphereMesh = engine.resources.loadMesh(Primitive::Sphere);
  Shader &litShader = engine.resources.loadShader("assets/shaders/lit.vert", "assets/shaders/lit.frag");
  Shader &basicShader = engine.resources.loadShader( "assets/shaders/basic.vert", "assets/shaders/basic.frag");
  Texture &earthDiff = engine.resources.loadTexture("assets/textures/earth.jpg", false);
  Texture &earthSpec = engine.resources.loadTexture("assets/textures/earth_spec.jpg", false);

  // Materials
  Material &sunMat = engine.resources.createMaterial("sun", basicShader)
    .setColor({1.0f, 0.75f, 0.3f});

  Material &earthMat = engine.resources.createMaterial("earth", litShader)
    .setDiffuseTexture(earthDiff)
    .setSpecularTexture(earthSpec)
    .setShininess(80.0f);

  // Scene
  MeshNode &sun = engine.scene.createNode<MeshNode>("sun")
    .setMesh(sphereMesh)
    .setMaterial(sunMat)
    .setScale({3.0f, 3.0f, 3.0f})
    .setPosition({0.0f, 0.0f, -5.0f});

  sun.createChild<LightNode>("sunLight")
    .setIntensity(4.5f)
    .setColor({1.0f, 0.72f, 0.4f});

  MeshNode &earth = sun.createChild<MeshNode>("earth")
    .setMesh(sphereMesh)
    .setMaterial(earthMat)
    .setPosition({3.0f, 0.0f, 0.0f});

  // Loop
  engine.onUpdate([&]() {
    if (engine.input.isKeyJustPressed(Key::Escape)) 
      engine.quit();

    float dt = engine.time.getDeltaTime();
    sun.rotate(dt * 5.0f, {0.0f, 1.0f, 0.0f});
    earth.rotate(dt * 60.0f, {0.0f, 1.0f, 0.0f});
  });

  engine.run();
}