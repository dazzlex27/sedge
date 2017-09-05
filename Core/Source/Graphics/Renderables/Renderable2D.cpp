/*
===========================================================================
Renderable2D.cpp

Implements the Renderable2D class.
===========================================================================
*/

#include "Renderable2D.h"
#include "System/Log.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Renderers/Renderer2D.h"

using namespace s3dge;

Renderable2D::Renderable2D()
	: Col(0xffffffff), Position(0, 0, 0), Size(0, 0), Texture(nullptr)
{
}

Renderable2D::Renderable2D(const Vector3& position, const Size2D& size, const Color& color)
	: Position(position), Size(size), Col(color), Texture(nullptr)
{
}

Renderable2D::Renderable2D(const Vector3& position, const Size2D& size, Texture2D*const texture)
	: Position(position), Size(size), Col(0xffffffff), Texture(texture)
{
}

Renderable2D::~Renderable2D()
{
}

void Renderable2D::SetColor(const Color& color) 
{ 
	Col = color;
}

void Renderable2D::SetPosition(const Vector2& position)
{
	Position = Vector3(position.x, position.y, Position.z);
}

void Renderable2D::SetZIndex(const float zIndex)
{
	Position.z = zIndex;
}

void Renderable2D::Submit(Renderer2D*const renderer) const
{
	renderer->Submit(this);
}

const uint Renderable2D::GetTextureID() const
{
	return Texture == nullptr ? 0 : Texture->GetID();
}