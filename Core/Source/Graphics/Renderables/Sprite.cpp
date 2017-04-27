/*
===========================================================================
Sprite.cpp

Implements the Sprite class
===========================================================================
*/

#include "Sprite.h"

using namespace s3dge;
using namespace graphics;
	
Sprite::Sprite(const Point2D& position, const Size2D& size, const Color& color)
	: Renderable2D(Point3D(position.x, position.y, 0), size, color), position(_position)
{
}

Sprite::Sprite(const Point2D& position, const Size2D& size, Texture2D* texture)
	: Renderable2D(Point3D(position.x, position.y, 0), size, texture), position(_position)
{
}