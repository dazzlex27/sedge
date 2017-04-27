/*
===========================================================================
Label.cpp

Implements the Label class
===========================================================================
*/

#include "Label.h"
#include "Graphics/Fonts/Font.h"
#include "Graphics/Renderers/Renderer2D.h"

using namespace s3dge;
using namespace graphics;
using namespace math;
	
Label::Label(const std::string& text, Font* font, const Point2D& position, const Size2D& size, const Color& color)
	: Renderable2D(Point3D(position.x, position.y, 0), size, color)
{
	this->text = text;
	this->font = font;
}

void Label::Submit(Renderer2D* renderer) const
{
	renderer->DrawString(text, font, Vector3(_position.x, _position.y, 0), _color);
}