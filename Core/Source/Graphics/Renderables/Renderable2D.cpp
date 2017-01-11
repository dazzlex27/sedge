/*
===========================================================================
Renderable2D.cpp

Contains method implementations for Renderable2D
===========================================================================
*/

#include "Renderable2D.h"
#include "Utilities/Converters.h"

using namespace s3dge;
using namespace graphics;
using namespace maths;

Renderable2D::Renderable2D()
	: _texture(nullptr)
{
	SetDefaultUVConfiguration();
}

Renderable2D::Renderable2D(const vec3f& position, const vec2f& size, uint color)
	: _position(position), _size(size), _color(color), _texture(nullptr)
{
	SetDefaultUVConfiguration();
}

Renderable2D::~Renderable2D()
{
}

void Renderable2D::Submit(Renderer2D* renderer) const
{
	renderer->Submit(this);
}

void Renderable2D::SetDefaultUVConfiguration()
{
	_uv.push_back(maths::vec2f(0, 0));
	_uv.push_back(maths::vec2f(0, 1));
	_uv.push_back(maths::vec2f(1, 1));
	_uv.push_back(maths::vec2f(1, 0));
}

void Renderable2D::SetColor(uint color) 
{ 
	_color = color; 
}

void Renderable2D::SetColor(const maths::vec4f& color) 
{ 
	_color = ConvertColorToUint(color); 
}