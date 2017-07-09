#include "Renderable.h"
#include "Graphics/Renderers/Renderer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Structures/VertexData.h"

using namespace s3dge;

Renderable::Renderable(VertexData* vertices, uint vertexCount, uint* elements, uint elementCount)
	: Vertices(vertices), VertexCount(vertexCount), Elements(elements), ElementCount(elementCount), Texture(nullptr)
{
}

Renderable::Renderable(VertexData* vertices, uint vertexCount, uint* elements, uint elementCount, Texture2D* texture)
	: Vertices(vertices), VertexCount(vertexCount), Elements(elements), Texture(texture)
{
}

void Renderable::Submit(Renderer* renderer)
{
	renderer->Submit(this);
}