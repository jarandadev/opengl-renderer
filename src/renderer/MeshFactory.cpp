#include "MeshFactory.h"
#include <cmath>
#include <glm/gtc/constants.hpp>
#include <vector>

std::shared_ptr<Mesh> MeshFactory::Create(Primitive type) {
  switch (type) {
  case Primitive::Cube:
    return CreateCube();
  case Primitive::Plane:
    return CreatePlane();
  case Primitive::Sphere:
    return CreateSphere();
  default:
    return nullptr;
  }
}

std::shared_ptr<Mesh> MeshFactory::CreateCube() {
  std::vector<Vertex> vertices = {{{-0.5f, -0.5f, 0.5f}, {0, 0, 1}, {0, 0}},
                                  {{0.5f, -0.5f, 0.5f}, {0, 0, 1}, {1, 0}},
                                  {{0.5f, 0.5f, 0.5f}, {0, 0, 1}, {1, 1}},
                                  {{-0.5f, 0.5f, 0.5f}, {0, 0, 1}, {0, 1}},
                                  {{0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0, 0}},
                                  {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 0}},
                                  {{-0.5f, 0.5f, -0.5f}, {0, 0, -1}, {1, 1}},
                                  {{0.5f, 0.5f, -0.5f}, {0, 0, -1}, {0, 1}},
                                  {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 0}},
                                  {{-0.5f, -0.5f, 0.5f}, {-1, 0, 0}, {1, 0}},
                                  {{-0.5f, 0.5f, 0.5f}, {-1, 0, 0}, {1, 1}},
                                  {{-0.5f, 0.5f, -0.5f}, {-1, 0, 0}, {0, 1}},
                                  {{0.5f, -0.5f, 0.5f}, {1, 0, 0}, {0, 0}},
                                  {{0.5f, -0.5f, -0.5f}, {1, 0, 0}, {1, 0}},
                                  {{0.5f, 0.5f, -0.5f}, {1, 0, 0}, {1, 1}},
                                  {{0.5f, 0.5f, 0.5f}, {1, 0, 0}, {0, 1}},
                                  {{-0.5f, 0.5f, 0.5f}, {0, 1, 0}, {0, 0}},
                                  {{0.5f, 0.5f, 0.5f}, {0, 1, 0}, {1, 0}},
                                  {{0.5f, 0.5f, -0.5f}, {0, 1, 0}, {1, 1}},
                                  {{-0.5f, 0.5f, -0.5f}, {0, 1, 0}, {0, 1}},
                                  {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0, 0}},
                                  {{0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 0}},
                                  {{0.5f, -0.5f, 0.5f}, {0, -1, 0}, {1, 1}},
                                  {{-0.5f, -0.5f, 0.5f}, {0, -1, 0}, {0, 1}}};

  std::vector<unsigned int> indices;
  for (unsigned int i = 0; i < 6; ++i) {
    unsigned int b = i * 4;
    indices.insert(indices.end(), {b, b + 1, b + 2, b, b + 2, b + 3});
  }
  return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> MeshFactory::CreatePlane() {
  std::vector<Vertex> vertices = {{{-0.5f, 0.0f, 0.5f}, {0, 1, 0}, {0, 0}},
                                  {{0.5f, 0.0f, 0.5f}, {0, 1, 0}, {1, 0}},
                                  {{0.5f, 0.0f, -0.5f}, {0, 1, 0}, {1, 1}},
                                  {{-0.5f, 0.0f, -0.5f}, {0, 1, 0}, {0, 1}}};
  std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
  return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> MeshFactory::CreateSphere() {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  const int rings = 16, sectors = 16;
  const float radius = 0.5f;

  for (int r = 0; r <= rings; ++r) {
    float v = 1.0f - (float)r / (float)rings;
    float phi = v * glm::pi<float>();
    for (int s = 0; s <= sectors; ++s) {
      float u = (float)s / (float)sectors;
      float theta = u * glm::two_pi<float>();

      glm::vec3 pos = {radius * std::sin(phi) * std::cos(theta),
                       radius * std::cos(phi),
                       radius * std::sin(phi) * std::sin(theta)};
      vertices.push_back({pos, glm::normalize(pos), {u, v}});
    }
  }

  for (int r = 0; r < rings; ++r) {
    for (int s = 0; s < sectors; ++s) {
      unsigned int curr = static_cast<unsigned int>(r * (sectors + 1) + s);
      unsigned int next = curr + static_cast<unsigned int>(sectors + 1);

      indices.push_back(curr);
      indices.push_back(next);
      indices.push_back(curr + 1);
      indices.push_back(next);
      indices.push_back(next + 1);
      indices.push_back(curr + 1);
    }
  }
  return std::make_shared<Mesh>(vertices, indices);
}