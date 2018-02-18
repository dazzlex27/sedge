/*
===========================================================================
VertexBuffer.cpp

Implements the VertexBuffer class
===========================================================================
*/

#include "VertexBuffer.h"
#include "Graphics/Structures/VertexLayout.h"
#include "System/MemoryManagement.h"
#include "Graphics/GraphicsAPI.h"

using namespace s3dge;

VertexBuffer::VertexBuffer(uint vertexSize, uint vertexCount, const VertexLayout& layout, void*const dataPtr, DrawingMode drawingMode)
	: Buffer(Array, vertexSize, vertexCount, dataPtr, drawingMode)
{
	_layout = new VertexLayout(layout);
}

VertexBuffer::~VertexBuffer()
{
	SafeDelete(_layout);
}

void VertexBuffer::Bind() const
{
	Buffer::Bind();
	const std::vector<LayoutAttribute*> atbs = _layout->GetAttributes();

	for (uint i = 0; i < atbs.size(); i++)
	{
		GraphicsAPI::EnableVertexAttributeArray(atbs[i]->index);
		GraphicsAPI::VertexAttributePointer(atbs[i]->index, atbs[i]->size, atbs[i]->type, atbs[i]->normalized, atbs[i]->stride, atbs[i]->offset);
	}
}

void VertexBuffer::BindLayout() const
{
}
