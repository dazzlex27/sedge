/*
===========================================================================
Buffer.cpp

Implements the Buffer class
===========================================================================
*/

#include "VertexBuffer.h"
#include <GL/glew.h>
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Structures/VertexData.h"

using namespace s3dge;
using namespace graphics;
	
VertexBuffer::VertexBuffer(void* data, int componentSize, uint componentCount)
	: _componentCount(componentCount), _data(data)
{
	glGenBuffers(1, &_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
	glBufferData(GL_ARRAY_BUFFER, componentCount * componentSize, data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(int componentSize, uint componentCount)
	: _componentCount(componentCount)
{
	glGenBuffers(1, &_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
	glBufferData(GL_ARRAY_BUFFER, componentCount * componentSize, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_bufferID);
}

void VertexBuffer::SetLayout(VertexLayout* layout)
{
	std::vector<LayoutAttribute*> atbs = layout->GetAttributes();

	Bind();

	for (uint i = 0; i < atbs.size(); i++)
	{
		glEnableVertexAttribArray(atbs[i]->index);
		glVertexAttribPointer(atbs[i]->index, atbs[i]->size, atbs[i]->type, atbs[i]->normalized, atbs[i]->stride, atbs[i]->offset);
	}

	Unbind();
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Map()
{
	_data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void VertexBuffer::Unmap()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}