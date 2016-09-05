#pragma once

#include<deque>
#include <GL/glew.h>
#include "S3DGETypes.h"
#include "Shaders/ShaderProgram.h"
#include <time.h>
#include "Maths/MathsHeader.h"
#include "Buffers/Buffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/Buffer.h"
#include "Graphics/Renderables/Renderable2D.h"

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
			std::deque<const Renderable2D*> m_Renderables;

		public:
			Renderer2D(ShaderProgram* shaderProgram);
			~Renderer2D();

			void Submit(Renderable2D* renderable);
			void Flush();

		private:
			void Initialize();
		};
	}
}