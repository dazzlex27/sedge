/*
===========================================================================
Renderable.h

Declares the Renderable class, which is the base class for all elements that can be drawn to the screen.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	struct VertexData;
	class Texture2D;
	class Renderer;

	class Renderable
	{
	protected:
		uint VertexCount;
		VertexData* Vertices;
		uint ElementCount;
		uint* Elements;
		Texture2D* Texture;

	public:
		Renderable(VertexData* vertices, uint vertexCount, uint* elements, uint elementCount, Texture2D* texture = nullptr);

		virtual void Submit(Renderer* renderer) const;

		const VertexData* GetVertexData() const { return Vertices; }
		const uint GetVertexCount() const { return VertexCount; }
		const uint* GetElementData() const { return Elements; }
		const uint GetElementCount() const { return ElementCount; }
		const Texture2D* GetTexture() const { return Texture; }
		virtual const uint GetTextureID() const;
	};
}