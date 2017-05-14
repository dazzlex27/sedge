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

Label::Label(const std::string& text, Font* font, const Point2D& position, float zIndex, const Size2D& size, const Color& color)
	: Renderable2D(Point3D(position.x, position.y, zIndex), size, color)
{
	this->text = text;
	this->font = font;
}

void Label::Submit(Renderer2D* renderer) const
{
	renderer->DrawString(text, font, Position, Col);
}