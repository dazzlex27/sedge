/*
===========================================================================
Sprite.cpp

Implements the Sprite class
===========================================================================
*/

#include "Sprite.h"

using namespace s3dge;
using namespace graphics;
	
Sprite::Sprite(float x, float y, float width, float height, const Color& color)
	: Renderable2D(Point3D(x, y, 0), math::vec2f(width, height), color), position(_position)
{
}

Sprite::Sprite(float x, float y, float width, float height, Texture2D* texture)
	: Renderable2D(Point3D(x, y, 0), math::vec2f(width, height), texture), position(_position)
{
}