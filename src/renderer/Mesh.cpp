#include "Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<unsigned int> &indices) {
  m_indexCount = static_cast<unsigned int>(indices.size());

  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);

  glBindVertexArray(m_vao);

  // Upload vertex data
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
               vertices.data(), GL_STATIC_DRAW);

  // Upload index data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               indices.data(), GL_STATIC_DRAW);

  // Define vertex attribute layout
  glEnableVertexAttribArray(0); // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void *>(offsetof(Vertex, position)));

  glEnableVertexAttribArray(1); // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void *>(offsetof(Vertex, normal)));

  glEnableVertexAttribArray(2); // TexCoords
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void *>(offsetof(Vertex, texCoords)));

  glBindVertexArray(0);
}

Mesh::~Mesh() {
  if (m_vao)
    glDeleteVertexArrays(1, &m_vao);
  if (m_vbo)
    glDeleteBuffers(1, &m_vbo);
  if (m_ebo)
    glDeleteBuffers(1, &m_ebo);
}

void Mesh::draw() const {
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}