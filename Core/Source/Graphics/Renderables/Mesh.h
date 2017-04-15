/*
===========================================================================
Mesh.h

Declares the Mesh class
===========================================================================
*/

#pragma once

#include "Math/Vector3.h"
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
		class Renderer;
		class VertexLayout;

		class Mesh
		{
		private:
			VertexArray* _vao;
			VertexBuffer* _vbo;
			IndexBuffer* _ibo;

		public:
			math::Vector3 translation;
			math::Vector3 scale;
			Texture2D* texture;
			Color color;

		private:
			Mesh(VertexBuffer* vbo, IndexBuffer* ibo, const Color& color = Color(0xffffffff));
			Mesh(VertexBuffer* vbo, IndexBuffer* ibo, Texture2D* texture);

		public:
			~Mesh();

		public:
			VertexArray* GetVAO() const { return _vao; }
			IndexBuffer* GetIBO() const { return _ibo; }

			void Submit(Renderer* renderer) const;
			void Render() const;

		private:
			VertexLayout GetDefaultVertexLayout();

			friend class MeshFactory;
		};
	}
}