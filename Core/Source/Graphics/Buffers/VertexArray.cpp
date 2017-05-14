/*
===========================================================================
VertexArray.cpp

Implements the VertexArray class
===========================================================================
*/

#include "VertexArray.h"
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "Graphics/Structures/VertexData.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
	
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_vertexArrayID);
}

VertexArray::~VertexArray()
{
	for (VertexBuffer* item : _buffers)
		SafeDelete(item);

	glDeleteVertexArrays(1, &_vertexArrayID);
}

void VertexArray::AddBuffer(VertexBuffer* buffer)
{
	_buffers.push_back(buffer);
}

void VertexArray::Bind() const
{
	glBindVertexArray(_vertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::Draw(uint indicesCount)
{
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}