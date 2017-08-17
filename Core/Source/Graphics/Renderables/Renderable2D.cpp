/*
===========================================================================
Renderable2D.cpp

Contains method implementations for Renderable2D
===========================================================================
*/

#include "Renderable2D.h"
#include "System/Log.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Renderers/Renderer2D.h"

using namespace s3dge;

static void SetVertexPosition(VertexData*const vertices, const uint vertexCount, const Vector2& position, const Size2D& size);

Renderable2D::Renderable2D()
	: Col(0xffffffff), Position(0, 0, 0), Size(0, 0), Renderable(nullptr, 0, nullptr, 0)
{
	PerformDefaultGeometrySetup();
}

Renderable2D::Renderable2D(const Vector3& position, const Size2D& size, const Color& color)
	: Position(position), Size(size), Col(color), Renderable(nullptr, 0, nullptr, 0)
{
	PerformDefaultGeometrySetup();
}

Renderable2D::Renderable2D(const Vector3& position, const Size2D& size, Texture2D*const texture)
	: Position(position), Size(size), Col(0xffffffff), Renderable(nullptr, 0, nullptr, 0)
{
	Texture = texture;
	PerformDefaultGeometrySetup();
}

Renderable2D::~Renderable2D()
{
}

void Renderable2D::PerformDefaultGeometrySetup()
{
	Vertices = new VertexData[4];

	Vertices[0].Position = Vector3(Position.x - Size.width / 2, Position.y - Size.height / 2, Position.z);
	Vertices[0].Color = Col;
	Vertices[0].Normal = Vector3(0.0f, 0.0f, 1.0f);
	Vertices[0].UV = Vector2(0, 0);
	Vertices[0].TextureID = (float)(Texture == nullptr ? 0 : Texture->GetID());

	Vertices[1].Position = Vector3(Position.x - Size.width / 2, Position.y + Size.height / 2, Position.z);
	Vertices[1].Color = Col;
	Vertices[0].Normal = Vector3(0.0f, 0.0f, 1.0f);
	Vertices[1].UV = Vector2(0, 1);
	Vertices[1].TextureID = (float)(Texture == nullptr ? 0 : Texture->GetID());

	Vertices[2].Position = Vector3(Position.x + Size.width / 2, Position.y + Size.height / 2, Position.z);
	Vertices[2].Color = Col;
	Vertices[0].Normal = Vector3(0.0f, 0.0f, 1.0f);
	Vertices[2].UV = Vector2(1, 1);
	Vertices[2].TextureID = (float)(Texture == nullptr ? 0 : Texture->GetID());

	Vertices[3].Position = Vector3(Position.x + Size.width / 2, Position.y - Size.height / 2, Position.z);
	Vertices[3].Color = Col;
	Vertices[0].Normal = Vector3(0.0f, 0.0f, 1.0f);
	Vertices[3].UV = Vector2(1, 0);
	Vertices[3].TextureID = (float)(Texture == nullptr ? 0 : Texture->GetID());

	VertexCount = 4;

	Elements = new uint[6];
	Elements[0] = 0;
	Elements[1] = 1;
	Elements[2] = 2;
	Elements[3] = 2;
	Elements[4] = 3;
	Elements[5] = 0;

	ElementCount = 6;
}

void Renderable2D::SetColor(const Color& color) 
{ 
	Col = color;

	for (uint i = 0; i < VertexCount; i++)
		Vertices[i].Color = Col;
}

void Renderable2D::SetPosition(const Vector2& position)
{
	Position = Vector3(position.x, position.y, Position.z);

	SetVertexPosition(Vertices, VertexCount, position, Size);
}

void Renderable2D::SetZIndex(const float zIndex)
{
	Position.z = zIndex;
}

void Renderable2D::Submit(Renderer2D*const renderer) const
{
	renderer->Submit(*this);
}

void SetVertexPosition(VertexData*const vertices, const uint vertexCount, const Vector2& position, const Size2D& size)
{
	if (vertexCount != 4)
	{
		LOG_FATAL("Disallowed default method is called for a Renderable2D instance. VertexCount != 4");
		abort();
	}

	vertices[0].Position = Vector3(position.x - size.width / 2, position.y - size.height / 2, 0);
	vertices[1].Position = Vector3(position.x - size.width / 2, position.y + size.height / 2, 0);
	vertices[2].Position = Vector3(position.x + size.width / 2, position.y + size.height / 2, 0);
	vertices[3].Position = Vector3(position.x - size.width / 2, position.y - size.height / 2, 0);
	
}
