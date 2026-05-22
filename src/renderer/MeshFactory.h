#pragma once

#include "Mesh.h"
#include <memory>

enum class Primitive { Cube, Sphere, Plane };

class MeshFactory {
public:
  // Creates a new mesh based on the primitive type
  static std::shared_ptr<Mesh> Create(Primitive type);

private:
  static std::shared_ptr<Mesh> CreateCube();
  static std::shared_ptr<Mesh> CreatePlane();
  static std::shared_ptr<Mesh> CreateSphere();
};