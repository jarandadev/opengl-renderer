#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

class Mesh {
public:
  Mesh(const std::vector<Vertex> &vertices,
       const std::vector<unsigned int> &indices);
  ~Mesh();

  // Prevent copies; use references instead
  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;

  void draw() const;

private:
  unsigned int m_vao = 0;
  unsigned int m_vbo = 0;
  unsigned int m_ebo = 0;
  unsigned int m_indexCount = 0;
};