/*
===========================================================================
SpriteFactory.h

Declares LabelFactory class that is responsible for creating Label instances.
===========================================================================
*/

#pragma once

#include <CustomTypes.h>
#include "Graphics/Structures/Color.h"

namespace sedge
{
	struct Vector2;
	struct Vector3;
	struct Size2D;

	class Texture2D;
	class Sprite;
	class Label;
	class Font;

	class SpriteFactory
	{
	public:
		static Sprite*const CreateSprite(const Vector2& position, const float zIndex, const Size2D& size, Texture2D*const texture);
		static Sprite*const CreateSprite(const Vector2& position, const float zIndex, const Size2D& size, const Color& color = 0xffffffff);
	};
}
