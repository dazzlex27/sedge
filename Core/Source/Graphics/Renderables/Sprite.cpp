/*
===========================================================================
Sprite.cpp

Implements the Sprite class
===========================================================================
*/

#include "Sprite.h"

using namespace s3dge;
using namespace graphics;
	
Sprite::Sprite(float x, float y, float width, float height, uint color)
	: Renderable2D(math::vec3f(x, y, 0), math::vec2f(width, height), color)
{
	this->position = _position;
}

Sprite::Sprite(float x, float y, float width, float height, Texture2D* texture)
	: Renderable2D(math::vec3f(x, y, 0), math::vec2f(width, height), 0xffffffff)
{
	this->position = _position;
	_texture = texture;
}