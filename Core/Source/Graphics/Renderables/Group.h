/*
===========================================================================
Group.h

Represents a class designed to contain groups of renderables together.
===========================================================================
*/

#pragma once

#include "Renderable2D.h"
#include "Graphics/Renderers/Renderer2D.h"

namespace s3dge
{
	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> _renderables;

	public:
		Group();
		~Group();

		void Add(Renderable2D* renderable);
		void Submit(Renderer2D* renderer);
	};
}