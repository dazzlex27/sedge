#pragma once

#include <GL/glew.h>
#include "Maths/mat4.h"
#include "CustomTypes.h"
#include "Utilities/FileIO.h"
#include "Maths/MathsHeader.h"

namespace s3dge
{
	namespace Graphics
	{
		class ShaderProgram
		{
		private:
			uint m_ProgramID;
			cstring m_Vertex;
			cstring m_Fragment;

		public:
			ShaderProgram(cstring vertex, cstring fragment);
			~ShaderProgram();

			void Enable();
			void Disable();

			void SetUniformMat4fv(cstring name, const Maths::mat4& matrix);
			void SetUniform1f(cstring name, float value);
			void SetUniform2f(cstring name, Maths::vec2f value);
			void SetUniform3f(cstring name, Maths::vec3f value);
			void SetUniform4f(cstring name, Maths::vec4f value);
			void SetUniform1i(cstring name, int value);
			void SetUniform1iv(cstring name, int count, int* value);

		private:
			uint Load();
			bool Compile(int shader);
		};
	}
}