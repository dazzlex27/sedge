/*
===========================================================================
Group.h

Represents a class designed to contain groups of renderables together.
===========================================================================
*/

#pragma once

#include <vector>
#include "Renderable2D.h"

namespace s3dge
{
	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> _renderables;

	public:
		Group();
		~Group();

		void Add(Renderable2D*const renderable);
		virtual void Submit(Renderer2D*const renderer) const override;

		virtual void Draw() const override {}
	};
}