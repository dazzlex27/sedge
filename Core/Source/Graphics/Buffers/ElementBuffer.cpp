/*
===========================================================================
ElementBuffer.cpp

Implements the ElementBuffer class
===========================================================================
*/

#include "ElementBuffer.h"
#include <GL/glew.h>

using namespace s3dge;

ElementBuffer::ElementBuffer(uint count, uint* data, DrawingMode drawingMode)
	: Buffer(sizeof(uint), count, data)
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

	glGenBuffers(1, &BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(data), data, mode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
}

void ElementBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}