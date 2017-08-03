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
		Renderable(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, Texture2D*const texture = nullptr);

		virtual void Submit(Renderer*const renderer) const;
		virtual void Draw() const { }

		const VertexData*const GetVertexData() const { return Vertices; }
		const uint GetVertexCount() const { return VertexCount; }
		const uint*const GetElementData() const { return Elements; }
		const uint GetElementCount() const { return ElementCount; }
		const Texture2D*const GetTexture() const { return Texture; }
		virtual const uint GetTextureID() const;
	};
}