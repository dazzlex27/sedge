/*
===========================================================================
Buffer.cpp

Implements the Buffer class
===========================================================================
*/

#include "Buffer.h"

using namespace s3dge;
using namespace graphics;
	
Buffer::Buffer(float* data, int count, uint componentCount)
	: _componentCount(componentCount)
{
	glGenBuffers(1, &_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &_bufferID);
}

void Buffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
}

void Buffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}