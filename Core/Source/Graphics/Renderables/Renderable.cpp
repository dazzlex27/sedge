/*
===========================================================================
Renderable.cpp

Implemlents the Renderable class
===========================================================================
*/

#include "Renderable.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Renderers/Renderer.h"
#include "System/DeleteMacros.h"

using namespace s3dge;

Renderable::Renderable(VertexData* vertices, uint vertexCount, uint* elements, uint elementCount, Texture2D* texture)
	: Vertices(vertices), VertexCount(vertexCount), Elements(elements), ElementCount(elementCount), Texture(texture)
{
}

void Renderable::Submit(Renderer* renderer) const
{
	renderer->Submit(this);
}

void Renderable::DisposeGeometry()
{
	SafeDeleteArray(Vertices);
	VertexCount = 0;
	SafeDeleteArray(Elements);
	ElementCount = 0;
}

const uint Renderable::GetTextureID() const
{
	return Texture == nullptr ? 0 : Texture->GetID();
}
