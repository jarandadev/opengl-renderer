#include "ResourceManager.h"
#include "renderer/Material.h"
#include "renderer/Mesh.h"
#include "renderer/Shader.h"

Mesh &ResourceManager::loadMesh(const std::string &path) {
  if (!m_meshes.contains(path)) {
    // TODO: Implement Assimp model loading
    m_meshes[path] = MeshFactory::Create(Primitive::Cube);
  }
  return *m_meshes[path];
}

Mesh &ResourceManager::loadMesh(Primitive type) {
  std::string key = "primitive_" + std::to_string(static_cast<int>(type));

  if (!m_meshes.contains(key)) {
    m_meshes[key] = MeshFactory::Create(type);
  }
  return *m_meshes[key];
}

Shader &ResourceManager::loadShader(const std::string &vPath,
                                    const std::string &fPath) {
  std::string key = vPath + fPath;
  if (!m_shaders.contains(key)) {
    m_shaders[key] = std::make_shared<Shader>(vPath, fPath);
  }
  return *m_shaders[key];
}

Texture &ResourceManager::loadTexture(const std::string &path,
                                      bool flipVertically) {
  if (!m_textures.contains(path)) {
    m_textures[path] = std::make_shared<Texture>(path, flipVertically);
  }
  return *m_textures[path];
}

Material &ResourceManager::createMaterial(const std::string &name,
                                          Shader &shader) {
  if (!m_materials.contains(name)) {
    m_materials[name] = std::make_shared<Material>(shader);
  }
  return *m_materials[name];
}