/*
===========================================================================
SpriteFactory.cpp

Implements the SpriteFactory class
===========================================================================
*/

#include "SpriteFactory.h"
#include "Graphics/Renderables/Sprite.h"

using namespace s3dge;

Sprite*const SpriteFactory::CreateSprite(const Vector2& position, const float zIndex, const Size2D& size, Texture2D*const texture)
{
	return new Sprite(position, zIndex, size, texture);
}

Sprite*const SpriteFactory::CreateSprite(const Vector2& position, const float zIndex, const Size2D& size, const Color& color)
{
	return new Sprite(position, zIndex, size, color);
}
