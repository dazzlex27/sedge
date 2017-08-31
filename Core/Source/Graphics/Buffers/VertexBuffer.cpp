/*
===========================================================================
VertexBuffer.cpp

Implements the VertexBuffer class
===========================================================================
*/

#include "VertexBuffer.h"

using namespace s3dge;

VertexBuffer::VertexBuffer(uint vertexSize, uint vertexCount, void*const dataPtr, DrawingMode drawingMode)
	: Buffer(Array, vertexSize, vertexCount, dataPtr, drawingMode)
{
}