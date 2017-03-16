#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <freetype-gl.h>

#include "Graphics/GraphicsStructures.h"

namespace s3dge
{
	namespace graphics
	{
		class Renderable2D;
		class IndexBuffer;
		class Font;
		struct Color;

		class Renderer2D
		{
		private:
			id _vao; // Vertex array object.
			id _vbo; // Vertex buffer object.
			IndexBuffer* _ibo; // Index buffer object.
			int _indexCount; // The number of indices.
			VertexData* _buffer; // Renderables container.
			std::vector<id> _textures; // Texture array.

		public:
			Renderer2D();	
			~Renderer2D();

			void Begin();
			void Submit(const Renderable2D* renderable);
			void Flush(); // OpenGL drawcall. 
			void End();

			void DrawString(const std::string& text, Font* font, const math::vec3f& position, const Color& color);

		private:
			void Initialize();
		};
	}
}