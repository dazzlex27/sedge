#pragma once

#include "Entity.h"

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