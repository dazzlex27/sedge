/*
===========================================================================
ElementBuffer.cpp

Implements the ElementBuffer class
===========================================================================
*/

#include "ElementBuffer.h"

using namespace s3dge;

ElementBuffer::ElementBuffer(const uint count, uint*const data, const DrawingMode drawingMode)
	: Buffer(Element, sizeof(*data), count, data, drawingMode)
{
}