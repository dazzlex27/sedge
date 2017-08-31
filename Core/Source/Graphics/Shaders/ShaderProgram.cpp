#include "ShaderProgram.h"
#include "System/Log.h"
#include "System/FileUtils.h"
#include "Graphics/GraphicsAPI.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"

using namespace s3dge;

ShaderProgram::ShaderProgram(const char*const name, const char*const vertexPath, const char*const fragmentPath)
	: _name(name), _vertexPath(vertexPath), _fragmentPath(fragmentPath)
{
	_programID = GraphicsAPI::CreateShaderProgram();
}

ShaderProgram::~ShaderProgram()
{
	GraphicsAPI::DetachShader(_programID, _vertexID);
	GraphicsAPI::DetachShader(_programID, _fragmentID);
	GraphicsAPI::DeleteShaderProgram(_programID);
}

const bool ShaderProgram::Load()
{
	// Create and compile vertex shader.
	_vertexID = GraphicsAPI::CreateShader(Vertex);
	std::string vertexSource = FileUtils::ReadFromFile(_vertexPath);

	if (vertexSource == "")
	{
		LOG_ERROR("Cannot find vertex shader source");
		return false;
	}

	GraphicsAPI::LoadShaderSource(_vertexID, vertexSource.c_str());

	if (!Compile(_vertexID))
	{
		GraphicsAPI::DeleteShader(_vertexID);
		return false;
	}

	// Create and compile fragment shader.
	_fragmentID = GraphicsAPI::CreateShader(Fragment);
	std::string fragmentSource = FileUtils::ReadFromFile(_fragmentPath);

	if (fragmentSource == "")
	{
		LOG_ERROR("Cannot find fragment shader source");
		return false;
	}

	GraphicsAPI::LoadShaderSource(_fragmentID, fragmentSource.c_str());

	if (!Compile(_fragmentID))
	{
		GraphicsAPI::DeleteShader(_vertexID);
		GraphicsAPI::DeleteShader(_fragmentID);
		return false;
	}

	GraphicsAPI::AttachShader(_programID, _vertexID);
	GraphicsAPI::AttachShader(_programID, _fragmentID);

	GraphicsAPI::LinkShaderProgram(_programID);
	GraphicsAPI::ValidateShaderProgram(_programID);

	GraphicsAPI::DeleteShader(_vertexID);
	GraphicsAPI::DeleteShader(_fragmentID);

	return true;
}

const bool ShaderProgram::Compile(const uint shader)
{
	// If the shader failed to compile, display the info log and return
	if (!GraphicsAPI::CompileShader(shader))
	{
		LOG_ERROR("shader compilation failed: ", GraphicsAPI::GetShaderInfoLog(shader));
		
		GraphicsAPI::DeleteShader(shader);

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
	GraphicsAPI::BindShaderProgram(_programID);
}

void ShaderProgram::Unbind() const
{
	GraphicsAPI::BindShaderProgram(0);
}

void ShaderProgram::SetUniformMat4fv(const char*const name, const Matrix4& matrix)
{
	GraphicsAPI::SetUniformMatrix4(GraphicsAPI::GetUniformLocation(_programID, name), 1, false, matrix.data);
}

void ShaderProgram::SetUniform1f(const char*const name, const float value)
{
	GraphicsAPI::SetUniform1f(GraphicsAPI::GetUniformLocation(_programID, name), value);
}

void ShaderProgram::SetUniform2f(const char*const name, const Vector2& value)
{
	GraphicsAPI::SetUniform2f(GraphicsAPI::GetUniformLocation(_programID, name), value.x, value.y);
}

void ShaderProgram::SetUniform3f(const char*const name, const Vector3& value)
{
	GraphicsAPI::SetUniform3f(GraphicsAPI::GetUniformLocation(_programID, name), value.x, value.y, value.z);
}

void ShaderProgram::SetUniform4f(const char*const name, const Vector4& value)
{
	GraphicsAPI::SetUniform4f(GraphicsAPI::GetUniformLocation(_programID, name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetUniform1i(const char*const name, const int value)
{
	GraphicsAPI::SetUniform1i(GraphicsAPI::GetUniformLocation(_programID, name), value);
}

void ShaderProgram::SetUniform1iv(const char*const name, const int count, const int*const value)
{
	GraphicsAPI::SetUniform1iv(GraphicsAPI::GetUniformLocation(_programID, name), count, value);
}