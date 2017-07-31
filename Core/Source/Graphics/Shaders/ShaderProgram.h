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
		cstring _vertexPath;
		cstring _fragmentPath;
		uint _vertex;
		uint _fragment;

		int _textureIDs[16]
		{
			0,1,2,3,4,5,6,7,8,9,
			10,11,12,13,14,15,
		};

	public:
		ShaderProgram(cstring vertex, cstring fragment);
		~ShaderProgram();

		void Enable() const;
		void Disable() const;

		void SetUniformMat4fv(cstring name, const Matrix4& matrix);
		void SetUniform1f(cstring name, const float value);
		void SetUniform2f(cstring name, const Vector2& value);
		void SetUniform3f(cstring name, const Vector3& value);
		void SetUniform4f(cstring name, const Vector4& value);
		void SetUniform1i(cstring name, const int value);
		void SetUniform1iv(cstring name, const int count, const int* value);

		void SetProjection(const Matrix4& projectionMatrix);
		void SetView(const Matrix4& viewMatrix);
		void SetModel(const Matrix4& modelMatrix);

	private:
		const uint Load();
		const bool Compile(const uint shader);
	};
}