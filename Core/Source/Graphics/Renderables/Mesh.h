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
		id* Textures;
		const uint TextureCount;

	private:
		Mesh(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, id*const texture = nullptr, const uint textureCount = 0);

	public:
		~Mesh();

		virtual void Draw() const override;

		friend class MeshFactory;
	};
}