#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix4;

	class ShaderProgram
	{
	private:
		uint _programID;
		const char* _vertexPath;
		const char* _fragmentPath;
		uint _vertex;
		uint _fragment;

		int _textureIDs[16]
		{
			0,1,2,3,4,5,6,7,8,9,
			10,11,12,13,14,15,
		};

	public:
		ShaderProgram(const char* vertex, const char* fragment);
		~ShaderProgram();

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

	private:
		const uint Load();
		const bool Compile(const uint shader);
	};
}