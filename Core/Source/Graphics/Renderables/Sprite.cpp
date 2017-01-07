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
	: Renderable2D(maths::vec3f(x, y, 0), maths::vec2f(width, height), color)
{
	this->position = _position;
}

Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
	: Renderable2D(maths::vec3f(x, y, 0), maths::vec2f(width, height), 0xffffffff)
{
	this->position = _position;
	_texture = texture;
}