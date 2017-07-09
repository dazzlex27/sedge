/*
===========================================================================
Mesh.h

Declares the Mesh class
===========================================================================
*/

#pragma once

#include "Renderable.h"
#include "Math/Vector3.h"
#include "Graphics/Structures/Color.h"

namespace s3dge
{
	struct VertexData;
	class ElementBuffer;
	class Texture2D;
	class Renderer;

	class Mesh : public Renderable
	{
	public:
		Texture2D* texture;

	private:
		Mesh(VertexData* vertices, uint vertexCount, uint* elements, uint elementCount);
		Mesh(VertexData* vertices, uint vertexCount, uint* elements, uint elementCount, Texture2D* texture);

		friend class MeshFactory;
	};
}