/*
===========================================================================
Renderable2D.cpp

Contains method implementations for Renderable2D
===========================================================================
*/

#include "Renderable2D.h"
#include "Graphics/Renderers/Renderer2D.h"

using namespace s3dge;

Renderable2D::Renderable2D()
	: Texture(nullptr), Col(0xffffffff), Position(0, 0, 0), Size(0, 0)
{
	SetDefaultUVConfiguration();
}

Renderable2D::Renderable2D(const Point3D& position, const Size2D& size, const Color& color)
	: Position(position), Size(size), Col(color), Texture(nullptr)
{
	SetDefaultUVConfiguration();
}

Renderable2D::Renderable2D(const Point3D& position, const Size2D& size, Texture2D* texture)
	: Position(position), Size(size), Col(0xffffffff), Texture(texture)
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
	Uv.push_back(Point2D(0, 0));
	Uv.push_back(Point2D(0, 1));
	Uv.push_back(Point2D(1, 1));
	Uv.push_back(Point2D(1, 0));
}

void Renderable2D::SetColor(const Color& color) 
{ 
	Col = color; 
}

void Renderable2D::SetPosition(const Point3D& position)
{
	Position = position;
}

void Renderable2D::SetZIndex(float zIndex)
{
	Position.z = zIndex;
}
