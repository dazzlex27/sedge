#pragma once

#include <GL/glew.h>
#include "S3DGETypes.h"
#include "Utilities/FileIO.h"
#include "Maths/MathsHeader.h"

namespace S3DGE
{
	namespace Graphics
	{
		class ShaderProgram
		{
		private:
			uint m_ProgramID;
			const char* m_Vertex;
			const char* m_Fragment;

		public:
			ShaderProgram(const char* vertex, const char* fragment);
			~ShaderProgram();

			void Enable();
			void Disable();

			void ShaderProgram::SetUniform1f(const char* name, float value);
			void ShaderProgram::SetUniform2f(const char* name, Maths::vec2f value);
			void ShaderProgram::SetUniform3f(const char* name, Maths::vec3f value);
			void ShaderProgram::SetUniform4f(const char* name, Maths::vec4f value);
			void ShaderProgram::SetUniform1i(const char* name, int value);

		private:
			uint Load();
			bool Compile(int shader);
		};
	}
}