/*
===========================================================================
IndexBuffer.cpp

Implements the IndexBuffer class
===========================================================================
*/

#include "IndexBuffer.h"

using namespace sedge;

IndexBuffer::IndexBuffer(const uint count, uint*const data, const DrawingMode drawingMode)
	: Buffer(Element, sizeof(*data), count, data, drawingMode)
{
}