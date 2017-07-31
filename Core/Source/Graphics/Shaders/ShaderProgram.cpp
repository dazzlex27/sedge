#include "ShaderProgram.h"
#include <GL/glew.h>
#include "System/Log.h"
#include "System/FileUtils.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"

using namespace s3dge;

ShaderProgram::ShaderProgram(cstring vertexPath, cstring fragmentPath)
	: _vertexPath(vertexPath), _fragmentPath(fragmentPath)
{
	_programID = Load();
	Enable();
	SetUniform1iv("textureArray", 16, _textureIDs);
}

ShaderProgram::~ShaderProgram()
{
	glDetachShader(_programID, _vertex);
	glDetachShader(_programID, _fragment);
	glDeleteProgram(_programID);
}

const uint ShaderProgram::Load()
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

const bool ShaderProgram::Compile(const uint shader)
{
	glCompileShader(shader);

	// Check the compilation status and report any errors
	int shaderStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderStatus);

	// If the shader failed to compile, display the info log and return
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

void ShaderProgram::SetProjection(const Matrix4& matrix)
{
	Enable();
	SetUniformMat4fv("pr_matrix", matrix);
}

void ShaderProgram::SetView(const Matrix4& matrix)
{
	Enable();
	SetUniformMat4fv("vw_matrix", matrix);
}

void ShaderProgram::SetModel(const Matrix4& matrix)
{
	Enable();
	SetUniformMat4fv("ml_matrix", matrix);
}

void ShaderProgram::Enable() const
{
	glUseProgram(_programID);
}

void ShaderProgram::Disable() const
{
	glUseProgram(0);
}

void ShaderProgram::SetUniformMat4fv(cstring name, const Matrix4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(_programID, name), 1, GL_FALSE, matrix.data);
}

void ShaderProgram::SetUniform1f(cstring name, const float value)
{
	glUniform1f(glGetUniformLocation(_programID, name), value);
}

void ShaderProgram::SetUniform2f(cstring name, const Vector2& value)
{
	glUniform2f(glGetUniformLocation(_programID, name), value.x, value.y);
}

void ShaderProgram::SetUniform3f(cstring name, const Vector3& value)
{
	glUniform3f(glGetUniformLocation(_programID, name), value.x, value.y, value.z);
}

void ShaderProgram::SetUniform4f(cstring name, const Vector4& value)
{
	glUniform4f(glGetUniformLocation(_programID, name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetUniform1i(cstring name, const int value)
{
	glUniform1i(glGetUniformLocation(_programID, name), value);
}

void ShaderProgram::SetUniform1iv(cstring name, const int count, const int* value)
{
	glUniform1iv(glGetUniformLocation(_programID, name), count, value);
}