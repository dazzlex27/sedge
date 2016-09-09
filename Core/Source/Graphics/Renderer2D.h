#pragma once

#include <GL/glew.h>
#include "S3DGETypes.h"
#include "Shaders/ShaderProgram.h"
#include "Maths/MathsHeader.h"
#include "Buffers/Buffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexArray.h"
#include "Graphics/Renderables/Renderable2D.h"

namespace S3DGE
{
	namespace Graphics
	{
		struct VertexData
		{
			Maths::vec3f vertex;
			uint color;
			Maths::vec2f uv;
			float textureID;
		};
		
		#define RENDERER_MAX_SPRITES	60000
		#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
		#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
		#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
		#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

		class Renderer2D
		{
		private:
			uint m_VAO; // Vertex array object.
			uint m_VBO; // Vertex buffer object.
			IndexBuffer* m_IBO; // Index buffer object.
			int m_IndexCount; 
			VertexData* m_Buffer; // Renderables container.
			std::vector<uint> m_Textures;

		public:
			Renderer2D();
			~Renderer2D();

			void Begin();
			void SubmitRenderable(const Renderable2D* renderable); // Load the renderables.
			void Flush(); // OpenGL drawcall. 
			void End();

		private:
			void Initialize();
		};
	}
}