/*
===========================================================================
Label.cpp

Implements the Label class
===========================================================================
*/

#include "Label.h"
#include <freetype-gl.h>
#include "System/MemoryManagement.h"
#include "Graphics/Fonts/Font.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Renderers/Renderer2D.h"

using namespace sedge;
using namespace ftgl;

Label::Label(const char*const text, Font*const font, const Vector2& position, const float zIndex, const Size2D& size, const Color& color)
	: _text(text), _font(font), Renderable2D(Vector3(position.x, position.y, zIndex), size, color)
{
}

void Label::SetText(const std::string& text)
{
	_text = text;
}

const uint Label::GetTextureID() const
{
	return _font->GetAtlasID();
}

void Label::Submit(Renderer2D*const renderer2d) const
{
	renderer2d->RenderText(_text.c_str(), _font, Position, Col);
}