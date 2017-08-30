/*
===========================================================================
VertexBuffer.cpp

Implements the VertexBuffer class
===========================================================================
*/

#include "VertexBuffer.h"
#include "Graphics/RenderSystem.h"

using namespace s3dge;

VertexBuffer::VertexBuffer(const uint vertexSize, const uint vertexCount, void*const data, const DrawingMode drawingMode)
	: Buffer(BufferTarget::Array, vertexSize, vertexCount, data, drawingMode)
{
}