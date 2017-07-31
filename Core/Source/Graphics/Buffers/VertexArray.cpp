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
#include "Graphics/Structures/VertexLayout.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
	
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_vertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_vertexArrayID);
}

void VertexArray::SetLayout(const VertexLayout& layout)
{
	const std::vector<LayoutAttribute*> atbs = layout.GetAttributes();

	Bind();

	for (uint i = 0; i < atbs.size(); i++)
	{
		glEnableVertexAttribArray(atbs[i]->index);
		glVertexAttribPointer(atbs[i]->index, atbs[i]->size, atbs[i]->type, atbs[i]->normalized, atbs[i]->stride, atbs[i]->offset);
	}

	Unbind();
}

void VertexArray::Bind() const
{
	glBindVertexArray(_vertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::Draw(const uint elementCount)
{
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, NULL);
}