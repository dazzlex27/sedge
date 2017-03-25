#pragma once

#include "Graphics/Structures/Color.h"

namespace s3dge
{
	namespace graphics
	{
		class VertexArray;
		class VertexBuffer;
		class IndexBuffer;
		class Renderer2D;
		class Texture2D;
		struct VertexData;

		class Mesh2D
		{
		private:
			VertexArray* _vao;
			VertexBuffer* _vbo;
			IndexBuffer* _ibo;
			Color _color;

		public:
			Mesh2D(VertexBuffer* vbo, IndexBuffer* ibo, const Color& color = Color(0xffffffff));
			~Mesh2D();

		public:
			VertexArray* GetVAO() const { return _vao; }
			IndexBuffer* GetIBO() const { return _ibo; }
			const Color& GetColor() const { return _color; }

			void Render();
		};
	}
}