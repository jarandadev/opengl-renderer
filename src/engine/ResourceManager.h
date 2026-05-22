#pragma once

#include "renderer/MeshFactory.h"
#include "renderer/Texture.h"

#include <memory>
#include <string>
#include <unordered_map>

class Mesh;
class Shader;
class Material;

class ResourceManager {
public:
  Mesh &loadMesh(const std::string &path);
  Mesh &loadMesh(Primitive type);
  Shader &loadShader(const std::string &vPath, const std::string &fPath);
  Texture &loadTexture(const std::string &path, bool flipVertically = true);
  Material &createMaterial(const std::string &name, Shader &shader);

private:
  std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
  std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
  std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
  std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
};