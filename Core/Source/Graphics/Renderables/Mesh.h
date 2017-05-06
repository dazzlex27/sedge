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
			Vector3 translation;
			Vector3 scale;
			Texture2D* texture;

		private:
			Mesh(VertexBuffer* vbo, IndexBuffer* ibo);
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