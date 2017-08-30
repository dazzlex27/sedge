/*
===========================================================================
VertexBuffer.cpp

Implements the VertexBuffer class
===========================================================================
*/

#include "VertexBuffer.h"
#include <GL/glew.h>

using namespace s3dge;

static int GetDrawingModeValue(const DrawingMode drawingMode)
{
	switch (drawingMode)
	{
	case DrawingMode::Dynamic:
		return GL_DYNAMIC_DRAW;
	case DrawingMode::Static:
		return GL_STATIC_DRAW;
	case DrawingMode::Stream:
		return GL_STREAM_DRAW;
	default:
		return 0;
	}
}

VertexBuffer::VertexBuffer(uint vertexSize, uint vertexCount, void*const dataPtr, DrawingMode drawingMode)
	: Buffer(vertexSize, vertexCount, dataPtr)
{
	glGenBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexCount, dataPtr, GetDrawingModeValue(drawingMode));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Map()
{
	DataPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void VertexBuffer::Unmap()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}