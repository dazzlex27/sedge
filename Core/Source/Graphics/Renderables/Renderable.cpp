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

Renderable::Renderable(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, Texture2D*const texture)
	: Vertices(vertices), VertexCount(vertexCount), Elements(elements), ElementCount(elementCount), Texture(texture)
{
}

void Renderable::Submit(Renderer*const renderer) const
{
	renderer->Submit(this);
}

const uint Renderable::GetTextureID() const
{
	return Texture == nullptr ? 0 : Texture->GetID();
}
