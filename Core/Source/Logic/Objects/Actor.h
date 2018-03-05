#pragma once

#include "Entity.h"

#include "Graphics/Renderables/Renderable.h"

namespace s3dge
{
	class Renderable;

	class Actor : public Entity
	{
	private:
		Renderable* _renderable;

	public:
		Actor(Renderable*const renderable);

		virtual void Update() override;
		virtual void Draw() override;
	};
}