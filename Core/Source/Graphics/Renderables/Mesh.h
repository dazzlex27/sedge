/*
===========================================================================
Mesh.h

Declares the Mesh class
===========================================================================
*/

#pragma once

#include "Renderable.h"

namespace s3dge
{
	struct VertexData;
	class VertexArray;
	class VertexBuffer;
	class ElementBuffer;
	class Texture2D;

	class Mesh : public Renderable
	{
	protected:
		VertexArray* VAO;
		VertexBuffer* VBO;
		ElementBuffer* EBO;

	private:
		Mesh(VertexData* vertices, uint vertexCount, uint* elements, uint elementCount, Texture2D* texture = nullptr);

	public:
		~Mesh();

		void Draw() const override;

		friend class MeshFactory;
	};
}