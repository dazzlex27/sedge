/*
===========================================================================
VertexBuffer.cpp

Implements the VertexBuffer class
===========================================================================
*/

#include "VertexBuffer.h"
#include <GL/glew.h>

using namespace s3dge;

static int GetDrawingModeValue(DrawingMode drawingMode)
{
	int mode = 0;

	switch (drawingMode)
	{
	case DrawingMode::DYNAMIC_DRAW:
		mode = GL_DYNAMIC_DRAW;
		break;
	case DrawingMode::STATIC_DRAW:
		mode = GL_STATIC_DRAW;
		break;
	case DrawingMode::STREAM_DRAW:
		mode = GL_STREAM_DRAW;
		break;
	}

	return mode;
}

VertexBuffer::VertexBuffer(int vertexSize, uint vertexCount, void* dataPtr, DrawingMode drawingMode)
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