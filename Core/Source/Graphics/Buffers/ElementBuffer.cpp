/*
===========================================================================
ElementBuffer.cpp

Implements the ElementBuffer class
===========================================================================
*/

#include "ElementBuffer.h"
#include "Graphics/RenderSystem.h"

using namespace s3dge;

ElementBuffer::ElementBuffer(const uint count, uint*const data, const DrawingMode drawingMode)
	: Buffer(BufferTarget::Element, sizeof(uint), count, data, drawingMode)
{
}