#pragma once

#include "Renderable.h"

namespace s3dge
{
	class Renderer3D;

	class Renderable3D : public Renderable
	{
	public:
		virtual void Draw() const = 0;
		virtual void Submit(Renderer3D*const renderer);
	};
}