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

int GetDrawingModeValue(DrawingMode drawingMode)
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

VertexBuffer::VertexBuffer(int elementSize, uint elementCount, void* dataPtr, DrawingMode drawingMode)
	: Buffer(elementSize, elementCount, dataPtr)
{
	glGenBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, elementSize * elementCount, dataPtr, GetDrawingModeValue(drawingMode));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &BufferID);
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