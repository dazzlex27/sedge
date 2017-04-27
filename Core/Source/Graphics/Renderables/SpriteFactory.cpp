/*
===========================================================================
SpriteFactory.cpp

Implements the SpriteFactory class
===========================================================================
*/

#include "SpriteFactory.h"
#include "Graphics/Renderables/Sprite.h"

using namespace s3dge;
using namespace graphics;

Sprite* SpriteFactory::CreateSprite(const Point2D& position, const Size2D& size, Texture2D* texture)
{
	return new Sprite(position, size, texture);
}

Sprite* SpriteFactory::CreateSprite(const Point2D& position, const Size2D& size, const Color& color)
{
	return new Sprite(position, size, color);
}
