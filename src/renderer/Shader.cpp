#include "Shader.h"

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

// Helper to check shader compilation and program linking errors
static void CheckCompileErrors(unsigned int shader, const std::string &type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                << infoLog << "\n";
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                << infoLog << "\n";
    }
  }
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure &e) {
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n"
              << "Tried paths:\n - Vert: " << vertexPath
              << "\n - Frag: " << fragmentPath << "\n";
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  CheckCompileErrors(vertex, "VERTEX");

  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  CheckCompileErrors(fragment, "FRAGMENT");

  m_id = glCreateProgram();
  glAttachShader(m_id, vertex);
  glAttachShader(m_id, fragment);
  glLinkProgram(m_id);
  CheckCompileErrors(m_id, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

Shader::~Shader() {
  if (m_id != 0)
    glDeleteProgram(m_id);
}

void Shader::use() const { glUseProgram(m_id); }

// Uniform setters
void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z,
                     float w) const {
  glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}