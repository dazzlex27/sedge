/*
===========================================================================
Mesh.cpp

Implemlents the Mesh class
===========================================================================
*/

#include "Mesh.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Renderers/Renderer.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Structures/VertexData.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
using namespace std;

Mesh::Mesh(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, Texture2D*const texture)
	: Renderable(vertices, vertexCount, elements, elementCount, texture)
{
	VAO = new VertexArray();
	VBO = new VertexBuffer(sizeof(VertexData), vertexCount, vertices);
	EBO = new ElementBuffer(elementCount, elements);

	VAO->Bind();
	VBO->Bind();
	EBO->Bind();

	VAO->SetLayout(VertexLayout::GetDefaultVertexLayout());

	VAO->Unbind();
	VBO->Unbind();
	EBO->Unbind();
}

Mesh::~Mesh()
{
	SafeDelete(VAO);
	SafeDelete(VBO);
	SafeDelete(EBO);
}

void Mesh::Draw() const
{
	if (Texture)
		Texture->Bind();

	VAO->Bind();
	VAO->Draw(EBO->GetCount());
	VAO->Unbind();
}
