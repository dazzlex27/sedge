#pragma once

#include <GL/glew.h>
#include "S3DGETypes.h"
#include "Shaders/ShaderProgram.h"
#include <time.h>
#include "Maths/MathsHeader.h"
#include "Buffers/Buffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/Buffer.h"

namespace S3DGE
{
	namespace Graphics
	{
		class Renderable2D; // Forward declaration.

		class Renderer2D
		{
		private:
			uint m_VAO; // Vertex array object.
			uint m_VBO; // Vertex buffer object.
			ShaderProgram* m_ShaderProgram; // Shader set.

		public:
			Renderer2D(ShaderProgram* shaderProgram);
			~Renderer2D();

			void Begin();
			void Submit(Renderable2D* renderable);
			void Flush();
			void End();

		private:
			void Initialize();
		};
	}
}