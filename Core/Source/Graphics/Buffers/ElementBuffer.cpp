/*
===========================================================================
ElementBuffer.cpp

Implements the ElementBuffer class
===========================================================================
*/

#include "ElementBuffer.h"
#include "System/DeleteMacros.h"
#include <GL/glew.h>

using namespace s3dge;

static int GetDrawingModeValue(const DrawingMode drawingMode)
{
	switch (drawingMode)
	{
	case DrawingMode::DYNAMIC_DRAW:
		return GL_DYNAMIC_DRAW;
	case DrawingMode::STATIC_DRAW:
		return GL_STATIC_DRAW;
	case DrawingMode::STREAM_DRAW:
		return GL_STREAM_DRAW;
	default:
		return 0;
	}
}

ElementBuffer::ElementBuffer(const uint count, uint*const data, const DrawingMode drawingMode)
	: Buffer(sizeof(uint), count, data)
{
	glGenBuffers(1, &BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(data), data, GetDrawingModeValue(drawingMode));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void ElementBuffer::Map()
{
	DataPtr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void ElementBuffer::Unmap()
{
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
}

void ElementBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}