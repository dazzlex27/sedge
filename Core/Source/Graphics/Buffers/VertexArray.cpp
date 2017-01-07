/*
===========================================================================
VertexArray.cpp

Implements the VertexArray class
===========================================================================
*/

#include "VertexArray.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace graphics;
	
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_vertexArrayID);
}

VertexArray::~VertexArray()
{
	for (Buffer* item : _buffers)
		SafeDelete(item);

	glDeleteVertexArrays(1, &_vertexArrayID);
}

void VertexArray::AddBuffer(Buffer* buffer, uint index)
{
	glBindVertexArray(_vertexArrayID);

	buffer->Bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
	buffer->Unbind();

	glBindVertexArray(0);
}

void VertexArray::Bind() const
{
	glBindVertexArray(_vertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}