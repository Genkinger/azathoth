#pragma once
#include "common.h"


class Shader {
private:
  GLuint m_Program;

public:
  Shader(const std::string &vertexPath, const std::string &fragmentPath);
  ~Shader();
  void Bind();
  void Unbind();
  void UniformMat4(std::string name, glm::mat4 matrix);
  void UniformVec3(std::string name, glm::vec3 vec);
  void UniformVec2(std::string name, glm::vec2 vec);
  void UniformInt(std::string name, int value);

private:
  void CompileShader(GLuint shader);
  GLuint LinkProgram(GLuint vertex, GLuint fragment);
  GLuint LoadShader(const std::string &vertexPath, const std::string &fragmentPath);
};
