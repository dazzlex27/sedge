/*
===========================================================================
SpriteFactory.cpp

Implements the SpriteFactory class
===========================================================================
*/

#include "SpriteFactory.h"
#include "Graphics/Renderables/Sprite.h"

using namespace s3dge;

Sprite* SpriteFactory::CreateSprite(const Point2D& position, float zIndex, const Size2D& size, Texture2D* texture)
{
	return new Sprite(position, zIndex, size, texture);
}

Sprite* SpriteFactory::CreateSprite(const Point2D& position, float zIndex, const Size2D& size, const Color& color)
{
	return new Sprite(position, zIndex, size, color);
}
