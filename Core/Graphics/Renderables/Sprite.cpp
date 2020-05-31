/*
===========================================================================
Sprite.cpp

Implements the Sprite class
===========================================================================
*/

#include "Sprite.h"

using namespace sedge;
	
Sprite::Sprite(const Vector2& position, const float zIndex, const Size2D& size, const Color& color)
	: Renderable2D(Vector3(position.x, position.y, zIndex), size, color)
{
}

Sprite::Sprite(const Vector2& position, const float zIndex, const Size2D& size, Texture2D*const texture)
	: Renderable2D(Vector3(position.x, position.y, zIndex), size, texture)
{
}