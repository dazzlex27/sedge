#pragma once

#include <GL/glew.h>
#include "Maths/mat4.h"
#include "CustomTypes.h"
#include "Utilities/FileUtils.h"
#include "Maths/MathsHeader.h"

namespace s3dge
{
	namespace graphics
	{
		class ShaderProgram
		{
		private:
			uint _programID;
			cstring _vertex;
			cstring _fragment;

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

			void SetUniformMat4fv(cstring name, const maths::mat4& matrix);
			void SetUniform1f(cstring name, float value);
			void SetUniform2f(cstring name, maths::vec2f value);
			void SetUniform3f(cstring name, maths::vec3f value);
			void SetUniform4f(cstring name, maths::vec4f value);
			void SetUniform1i(cstring name, int value);
			void SetUniform1iv(cstring name, int count, int* value);

			void SetProjection(maths::mat4 ortho);

		private:
			uint Load();
			bool Compile(int shader);
		};
	}
}