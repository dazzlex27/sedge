/*
===========================================================================
VertexArray.cpp

Implements the VertexArray class
===========================================================================
*/

#include "VertexArray.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/GraphicsAPI.h"

using namespace s3dge;
	
VertexArray::VertexArray()
{
	GraphicsAPI::GenVertexArrays(1, &_vertexArrayID);
}

VertexArray::~VertexArray()
{
	GraphicsAPI::DeleteVertexArrays(1, &_vertexArrayID);
}

void VertexArray::SetLayout(const VertexLayout& layout)
{
	const std::vector<LayoutAttribute*> atbs = layout.GetAttributes();

	Bind();

	for (uint i = 0; i < atbs.size(); i++)
	{
		GraphicsAPI::EnableVertexAttributeArray(atbs[i]->index);
		GraphicsAPI::VertexAttributePointer(atbs[i]->index, atbs[i]->size, atbs[i]->type, atbs[i]->normalized, atbs[i]->stride, atbs[i]->offset);
	}

	Unbind();
}

void VertexArray::Bind() const
{
	GraphicsAPI::BindVertexArray(_vertexArrayID);
}

void VertexArray::Unbind() const
{
	GraphicsAPI::BindVertexArray(0);
}

void VertexArray::DrawElements(const uint elementCount)
{
	GraphicsAPI::DrawElements(Triangles, elementCount, UnsignedInt, 0);
}