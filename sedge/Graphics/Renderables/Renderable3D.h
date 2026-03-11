/*
===========================================================================
Renderable3D.h

Base class for all 3D renderable objects.
===========================================================================
*/

#pragma once

#include "Renderable.h"

namespace sedge
{
	class Renderer3D;
	class VertexBuffer;
	class IndexBuffer;

	class Renderable3D : public Renderable
	{
	protected:
		VertexBuffer* VBO;
		IndexBuffer* IBO;

	public:
		virtual void Draw() const;
		virtual void Submit(Renderer3D*const renderer);
	};
}