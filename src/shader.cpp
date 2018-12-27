#include "shader.h"

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath): m_Program(LoadShader(vertexPath,fragmentPath)){}

void Shader::Bind() { glUseProgram(m_Program); }

void Shader::Unbind() { glUseProgram(0); }

void Shader::UniformMat4(std::string name, glm::mat4 matrix) {
  auto location = glGetUniformLocation(m_Program, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UniformVec3(std::string name, glm::vec3 vec) {
  auto location = glGetUniformLocation(m_Program, name.c_str());
  glUniform3fv(location, 1, glm::value_ptr(vec));
}

void Shader::UniformVec2(std::string name, glm::vec2 vec) {
  auto location = glGetUniformLocation(m_Program, name.c_str());
  glUniform2fv(location, 1, glm::value_ptr(vec));
}

void Shader::UniformInt(std::string name, int value) {
  auto location = glGetUniformLocation(m_Program, name.c_str());
  glUniform1i(location, value);
}

Shader::~Shader() { glDeleteProgram(m_Program); }


void Shader::CompileShader(GLuint shader)
{
	GLCall(glCompileShader(shader));
	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &Result));
	GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength));
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		GLCall(glGetShaderInfoLog(shader, InfoLogLength, nullptr,
						FragmentShaderErrorMessage.data()));
		printf("%s\n", FragmentShaderErrorMessage.data());
	}
}

GLuint Shader::LinkProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	GLCall(glAttachShader(ProgramID, vertexShader));
	GLCall(glAttachShader(ProgramID, fragmentShader));
	GLCall(glLinkProgram(ProgramID));

	// Check the program
	GLCall(glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result));
	GLCall(glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength));
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		GLCall(glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr,
							ProgramErrorMessage.data()));
		printf("%s\n", ProgramErrorMessage.data());
	}

	GLCall(glDetachShader(ProgramID, vertexShader));
	GLCall(glDetachShader(ProgramID, fragmentShader));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	return ProgramID;

}

GLuint Shader::LoadShader(const std::string& vertexPath,const std::string& fragmentPath)
{
	std::ifstream vertex_stream(vertexPath);
	std::ifstream fragment_stream(fragmentPath);
	std::string vertex_shader_string;
	std::string fragment_shader_string;
	
	vertex_stream.seekg(0,std::ios::end);
	vertex_shader_string.reserve(vertex_stream.tellg());
	vertex_stream.seekg(0,std::ios::beg);
	
	fragment_stream.seekg(0,std::ios::end);
	fragment_shader_string.reserve(fragment_stream.tellg());
	fragment_stream.seekg(0,std::ios::beg);

	vertex_shader_string.assign((std::istreambuf_iterator<char>(vertex_stream)),std::istreambuf_iterator<char>());
	fragment_shader_string.assign((std::istreambuf_iterator<char>(fragment_stream)),std::istreambuf_iterator<char>());
	
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *vertex_shader_string_const = vertex_shader_string.c_str();
	const GLchar *fragment_shader_string_const = fragment_shader_string.c_str();

	GLCall(glShaderSource(vertex_shader, 1, &vertex_shader_string_const, nullptr));
	GLCall(glShaderSource(fragment_shader, 1, &fragment_shader_string_const, nullptr));
	
	CompileShader(vertex_shader);
	CompileShader(fragment_shader);


	return LinkProgram(vertex_shader, fragment_shader);
}
