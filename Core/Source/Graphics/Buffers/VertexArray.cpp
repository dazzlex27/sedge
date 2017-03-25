/*
===========================================================================
VertexArray.cpp

Implements the VertexArray class
===========================================================================
*/

#include "VertexArray.h"
#include "Graphics/Structures/VertexData.h"
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

void VertexArray::AddBuffer(Buffer* buffer)
{
	glBindVertexArray(_vertexArrayID);

	buffer->Bind();
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Position)));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::UV)));
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::TextureID)));

	buffer->Unbind();

	_buffers.push_back(buffer);

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

void VertexArray::Draw(uint indicesCount)
{
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}