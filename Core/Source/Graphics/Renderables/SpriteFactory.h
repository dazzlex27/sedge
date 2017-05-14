/*
===========================================================================
SpriteFactory.h

Declares LabelFactory class that is responsible for creating Label instances.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Graphics/Structures/Color.h"

namespace s3dge
{
	struct Point2D;
	struct Size2D;

	class Texture2D;
	class Sprite;
	class Label;
	class Font;

	class SpriteFactory
	{
	public:
		static Sprite* CreateSprite(const Point2D& position, float zIndex, const Size2D& size, Texture2D* texture);
		static Sprite* CreateSprite(const Point2D& position, float zIndex, const Size2D& size, const Color& color = 0xffffffff);
	};
}
