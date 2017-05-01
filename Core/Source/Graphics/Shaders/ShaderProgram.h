#pragma once

#include "CustomTypes.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"

namespace s3dge
{
	namespace graphics
	{
		class ShaderProgram
		{
		private:
			uint _programID;
			cstring _vertexPath;
			cstring _fragmentPath;
			int _vertex;
			int _fragment;

			int _textureIDs[16]
			{
				0,1,2,3,4,5,6,7,8,9,
				10,11,12,13,14,15,
			};

		public:
			ShaderProgram(cstring vertex, cstring fragment);
			~ShaderProgram();

			void Enable();
			void Disable();

			void SetUniformMat4fv(cstring name, const math::Matrix4& matrix);
			void SetUniform1f(cstring name, float value);
			void SetUniform2f(cstring name, const math::Vector2& value);
			void SetUniform3f(cstring name, const math::Vector3& value);
			void SetUniform4f(cstring name, const math::Vector4& value);
			void SetUniform1i(cstring name, int value);
			void SetUniform1iv(cstring name, int count, int* value);

			void SetProjection(const math::Matrix4& projectionMatrix);
			void SetView(const math::Matrix4& viewMatrix);

		private:
			uint Load();
			bool Compile(int shader);
		};
	}
}