/*
===========================================================================
Mesh.h

Declares the Mesh class
===========================================================================
*/

#pragma once

#include "Renderable3D.h"

namespace s3dge
{
	struct VertexData;
	class VertexArray;
	class VertexBuffer;
	class ElementBuffer;
	class Texture2D;

	class Mesh : public Renderable3D
	{
	protected:
		VertexArray* VAO;
		VertexBuffer* VBO;
		ElementBuffer* EBO;

	private:
		Mesh(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, Texture2D*const texture = nullptr);

	public:
		~Mesh();

		virtual void Draw() const override;

		friend class MeshFactory;
	};
}