/*
===========================================================================
Label.cpp

Implements the Label class
===========================================================================
*/

#include "Label.h"
#include "Graphics/Fonts/Font.h"

using namespace s3dge;
using namespace graphics;
	
Label::Label(const std::string& text, Font* font, float x, float y, float width, float height, uint color)
	: Renderable2D(math::vec3f(x, y, 0), math::vec2f(width, height), color)
{
	this->text = text;
	this->position = math::vec2f(x, y);
	this->color = _color;
	this->font = font;
}

Label::~Label()
{
}

void Label::Submit(Renderer2D* renderer) const
{
	renderer->DrawString(text, font, math::vec3f(position.x, position.y, 0), color);
}