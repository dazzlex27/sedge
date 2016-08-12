#pragma once

#include <GL/glew.h>
#include "S3DGETypes.h"
#include "Shaders/ShaderProgram.h"
#include <time.h>
#include "Maths/vec4.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Renderer
		{
		private:
			uint m_VAO; // Vertex array object.
			ShaderProgram* m_ShaderProgram;

		public:
			Renderer(ShaderProgram* shaderProgram);
			~Renderer();

			void Draw();

		private:
			void Initialize();
		};
	}
}