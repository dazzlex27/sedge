#pragma once

#include "CustomTypes.h"
#include <string>

namespace s3dge
{
	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix4;

	class ShaderProgram
	{
	private:
		std::string _name;
		std::string _vertexPath;
		std::string _fragmentPath;
		id _programID;
		uint _vertexID;
		uint _fragmentID;

	private:
		ShaderProgram(const char*const name, const char*const vertexPath, const char*const fragmentPath);

	public:
		~ShaderProgram();

	public:
		const char*const GetName() const { return _name.c_str(); }
		const id GetProgramID() const { return _programID; }

		void Bind() const;
		void Unbind() const;

		void SetUniformMat4fv(const char* name, const Matrix4& matrix);
		void SetUniform1f(const char* name, const float value);
		void SetUniform2f(const char* name, const Vector2& value);
		void SetUniform3f(const char* name, const Vector3& value);
		void SetUniform4f(const char* name, const Vector4& value);
		void SetUniform1i(const char* name, const int value);
		void SetUniform1iv(const char* name, const int count, const int* value);

		void SetProjection(const Matrix4& projectionMatrix);
		void SetView(const Matrix4& viewMatrix);
		void SetModel(const Matrix4& modelMatrix);

		friend class ShaderFactory;

	private:
		const bool Load();
		const bool Compile(const uint shader);
	};
}