#pragma once

#include <GL/glew.h>
#include "S3DGETypes.h"
#include "Shaders/ShaderProgram.h"
#include <time.h>
#include "Maths/MathsHeader.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Renderer
		{
		private:
			uint m_VAO; // Vertex array object.
			uint m_VBO;
			ShaderProgram* m_ShaderProgram;

		public:
			Renderer(ShaderProgram* shaderProgram);
			~Renderer();

			void Flush();

		private:
			void Initialize();
		};
	}
}