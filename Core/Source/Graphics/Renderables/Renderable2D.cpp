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
using namespace math;

Renderable2D::Renderable2D()
	: _texture(nullptr), _color(0xffffffff), _position(0, 0, 0), _size(0, 0)
{
	SetDefaultUVConfiguration();
}

Renderable2D::Renderable2D(const Point3D& position, const Size2D& size, const Color& color)
	: _position(position), _size(size), _color(color), _texture(nullptr)
{
	SetDefaultUVConfiguration();
}

Renderable2D::Renderable2D(const Point3D& position, const Size2D& size, Texture2D* texture)
	: _position(position), _size(size), _color(0xffffffff), _texture(texture)
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
	_uv.push_back(Point2D(0, 0));
	_uv.push_back(Point2D(0, 1));
	_uv.push_back(Point2D(1, 1));
	_uv.push_back(Point2D(1, 0));
}

void Renderable2D::SetColor(const Color& color) 
{ 
	_color = color; 
}

void Renderable2D::SetPosition(const Point3D& position)
{
	_position = position;
}
