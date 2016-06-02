#include "ShaderProgram.h"
#include <GL/glew.h>
#include "System/Log.h"
#include "System/FileUtils.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"

using namespace s3dge;

ShaderProgram::ShaderProgram(const char*const name, const char*const vertexPath, const char*const fragmentPath)
	: _name(name), _vertexPath(vertexPath), _fragmentPath(fragmentPath)
{
	_programID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDetachShader(_programID, _vertexID);
	glDetachShader(_programID, _fragmentID);
	glDeleteProgram(_programID);
}

const bool ShaderProgram::Load()
{
	// Create and compile vertex shader.
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexSource = FileUtils::ReadFromFile(_vertexPath);

	if (vertexSource == "")
	{
		LOG_ERROR("Cannot find vertex shader source");
		return false;
	}

	const char* vSource = vertexSource.c_str();
	glShaderSource(_vertexID, 1, &vSource, NULL);

	if (!Compile(_vertexID))
		return false;

	// Create and compile fragment shader.
	_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentSource = FileUtils::ReadFromFile(_fragmentPath);

	if (fragmentSource == "")
	{
		LOG_ERROR("Cannot find fragment shader source");
		return false;
	}

	const char* fSource = fragmentSource.c_str();
	glShaderSource(_fragmentID, 1, &fSource, NULL);

	if (!Compile(_fragmentID))
		return false;

	glAttachShader(_programID, _vertexID);
	glAttachShader(_programID, _fragmentID);

	glLinkProgram(_programID);
	glValidateProgram(_programID);

	glDeleteShader(_vertexID);
	glDeleteShader(_fragmentID);

	return true;
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
	Bind();
	SetUniformMat4fv("pr_matrix", matrix);
}

void ShaderProgram::SetView(const Matrix4& matrix)
{
	Bind();
	SetUniformMat4fv("vw_matrix", matrix);
}

void ShaderProgram::SetModel(const Matrix4& matrix)
{
	Bind();
	SetUniformMat4fv("ml_matrix", matrix);
}

void ShaderProgram::Bind() const
{
	glUseProgram(_programID);
}

void ShaderProgram::Unbind() const
{
	glUseProgram(0);
}

void ShaderProgram::SetUniformMat4fv(const char* name, const Matrix4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(_programID, name), 1, GL_FALSE, matrix.data);
}

void ShaderProgram::SetUniform1f(const char* name, const float value)
{
	glUniform1f(glGetUniformLocation(_programID, name), value);
}

void ShaderProgram::SetUniform2f(const char* name, const Vector2& value)
{
	glUniform2f(glGetUniformLocation(_programID, name), value.x, value.y);
}

void ShaderProgram::SetUniform3f(const char* name, const Vector3& value)
{
	glUniform3f(glGetUniformLocation(_programID, name), value.x, value.y, value.z);
}

void ShaderProgram::SetUniform4f(const char* name, const Vector4& value)
{
	glUniform4f(glGetUniformLocation(_programID, name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetUniform1i(const char* name, const int value)
{
	glUniform1i(glGetUniformLocation(_programID, name), value);
}

void ShaderProgram::SetUniform1iv(const char* name, const int count, const int* value)
{
	glUniform1iv(glGetUniformLocation(_programID, name), count, value);
}