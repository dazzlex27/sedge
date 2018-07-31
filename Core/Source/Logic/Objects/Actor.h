#pragma once

#include "Entity.h"

namespace s3dge
{
	class Renderable;

	class Actor : public Entity
	{
	private:
		Renderable*const _renderable;

	public:
		Actor(Renderable*const renderable);
		virtual ~Actor();

		const Renderable*const GetRenderable() const { return _renderable; }

		virtual void Draw() override;

	protected:
		virtual void UpdateModelMatrix() override;
	};
}