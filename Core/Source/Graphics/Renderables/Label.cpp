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
using namespace math;
	
Label::Label(const std::string& text, Font* font, float x, float y, float width, float height, const Color& color)
	: Renderable2D(Point3D(x, y, 0), Size2D(width, height), color)
{
	this->text = text;
	this->font = font;
}

Label::~Label()
{
}

void Label::Submit(Renderer2D* renderer) const
{
	renderer->DrawString(text, font, Vector3(_position.x, _position.y, 0), _color);
}