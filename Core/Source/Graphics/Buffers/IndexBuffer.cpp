/*
===========================================================================
IndexBuffer.cpp

Implements the IndexBuffer class
===========================================================================
*/

#include "IndexBuffer.h"
#include <GL/glew.h>

using namespace s3dge;
using namespace graphics;

IndexBuffer::IndexBuffer(uint* data, uint count)
	: _count(count)
{
	glGenBuffers(1, &_bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_bufferID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}