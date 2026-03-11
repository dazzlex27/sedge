/*
===========================================================================
Renderable3D.cpp

Implements the Renderable3D class.
===========================================================================
*/

#include "Renderable3D.h"
#include "Graphics/GraphicsAPI.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"

using namespace sedge;

void Renderable3D::Draw() const
{
	VBO->Bind();
	IBO->Bind();
	GraphicsAPI::DrawTrianglesIndexed(IBO->GetCount());
}

void Renderable3D::Submit(Renderer3D*const renderer)
{
}