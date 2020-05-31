/*
===========================================================================
Sprite.h

Represents a renderable 2D object with position, size and a Z index.
===========================================================================
*/

#pragma once

#include "Renderable2D.h"

namespace s3dge
{
	class Sprite : public Renderable2D
	{
	private:
		Sprite(const Vector2& position, const float zIndex, const Size2D& size, const Color& color);
		Sprite(const Vector2& position, const float zIndex, const Size2D& size, Texture2D*const texture);

	public:
		virtual void Draw() const override {}

		friend class SpriteFactory;
	};
}