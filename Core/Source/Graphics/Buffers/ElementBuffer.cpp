/*
===========================================================================
ElementBuffer.cpp

Implements the ElementBuffer class
===========================================================================
*/

#include "ElementBuffer.h"
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

ElementBuffer::ElementBuffer(uint count, uint* data, DrawingMode drawingMode)
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