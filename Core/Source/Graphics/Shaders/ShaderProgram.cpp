#include "ShaderProgram.h"
#include "Internal/Log.h"

using namespace s3dge;
using namespace graphics;
	
ShaderProgram::ShaderProgram(cstring vertexPath, cstring fragmentPath)
	: _vertexPath(vertexPath), _fragmentPath(fragmentPath)
{
	_programID = Load();
	this->Enable();
	this->SetUniform1iv("textureArray", 16, _textureIDs);
}

ShaderProgram::~ShaderProgram()
{
	glDetachShader(_programID, _vertex);
	glDetachShader(_programID, _fragment);
	glDeleteProgram(_programID);
}

uint ShaderProgram::Load()
{
	// Create and compile vertex shader.
	_vertex = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexSource = FileUtils::ReadFromFile(_vertexPath).c_str();
	if (vertexSource == "")
	{
		LOG_ERROR("Cannot find vertex shader source");
		return -1;
	}
	cstring vSource = vertexSource.c_str();
	glShaderSource(_vertex, 1, &vSource, NULL);
	if (!Compile(_vertex))
		return -1;

	// Create and compile fragment shader.
	_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentSource = FileUtils::ReadFromFile(_fragmentPath).c_str();
	if (fragmentSource == "")
	{
		LOG_ERROR("Cannot find fragment shader source");
		return -1;
	}
	cstring fSource = fragmentSource.c_str();
	glShaderSource(_fragment, 1, &fSource, NULL);
	if (!Compile(_fragment))
		return -1;

	// Create a shader program and attach compiled shaders to it.
	int program = glCreateProgram();

	glAttachShader(program, _vertex);
	glAttachShader(program, _fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(_vertex);
	glDeleteShader(_fragment);

	return program;
}

bool ShaderProgram::Compile(int shader)
{
	glCompileShader(shader); // Compile the shader

	// Check the compilation status and report any errors
	int shaderStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderStatus);

	// If the shader failed to compile, display the info log and quit out
	if (shaderStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		char *strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, 0, strInfoLog);

		LOG_ERROR("shader compilation failed: ", strInfoLog);
		delete[] strInfoLog;
		glDeleteShader(shader);
		return false;
	}

	return true;
}

void ShaderProgram::SetProjection(math::mat4 matrix)
{
	this->Enable();
	this->SetUniformMat4fv("pr_matrix", matrix);
}

void ShaderProgram::Enable()
{
	glUseProgram(_programID);
}

void ShaderProgram::Disable()
{
	glUseProgram(0);
}

void ShaderProgram::SetUniformMat4fv(cstring name, const math::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(_programID, name), 1, GL_FALSE, matrix.elements);
}

void ShaderProgram::SetUniform1f(cstring name, float value)
{
	glUniform1f(glGetUniformLocation(_programID, name), value);
}

void ShaderProgram::SetUniform2f(cstring name, math::vec2f value)
{
	glUniform2f(glGetUniformLocation(_programID, name), value.x, value.y);
}

void ShaderProgram::SetUniform3f(cstring name, math::vec3f value)
{
	glUniform3f(glGetUniformLocation(_programID, name), value.x, value.y, value.z);
}

void ShaderProgram::SetUniform4f(cstring name, math::vec4f value)
{
	glUniform4f(glGetUniformLocation(_programID, name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetUniform1i(cstring name, int value)
{
	glUniform1i(glGetUniformLocation(_programID, name), value);
}

void ShaderProgram::SetUniform1iv(cstring name, int count, int* value)
{
	glUniform1iv(glGetUniformLocation(_programID, name), count, value);
}