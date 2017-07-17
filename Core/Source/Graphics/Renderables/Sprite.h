/*
===========================================================================
Sprite.h

Inherits from the Renderable2D.
===========================================================================
*/

#pragma once

#include "Renderable2D.h"

namespace s3dge
{
	class Sprite : public Renderable2D
	{
	private:
		Sprite(const Point2D& position, const float zIndex, const Size2D& size, const Color& color);
		Sprite(const Point2D& position, const float zIndex, const Size2D& size, Texture2D* texture);

		friend class SpriteFactory;
	};
}