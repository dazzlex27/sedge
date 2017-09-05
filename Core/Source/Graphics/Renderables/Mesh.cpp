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
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Structures/VertexData.h"
#include "System/DeleteMacros.h"
#include "Graphics/Managers/TextureManager.h"

using namespace s3dge;
using namespace std;

Mesh::Mesh(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, id*const textures, const uint textureCount)
	: TextureCount(textureCount)
{
	VAO = new VertexArray();
	VBO = new VertexBuffer(sizeof(VertexData), vertexCount, vertices);
	EBO = new ElementBuffer(elementCount, elements);

	VAO->Bind();
	VBO->Bind();
	EBO->Bind();

	VAO->SetLayout(VertexLayout::GetDefaultMeshVertexLayout());

	VAO->Unbind();
	VBO->Unbind();
	EBO->Unbind();

	if (TextureCount > 0 && textures)
	{
		Textures = new id[TextureCount];
		for (uint i = 0; i < TextureCount; i++)
			Textures[i] = textures[i];
	}
}

Mesh::~Mesh()
{
	SafeDelete(VAO);
	SafeDelete(VBO);
	SafeDelete(EBO);
}

void Mesh::Draw() const
{
	if (TextureCount > 0)
	{
		for (uint i = 0; i < TextureCount; i++)
		{
			Texture2D* texture = TextureManager::GetTex2DByID(Textures[i]);

			if (!texture)
				continue;

			Texture2D::ActivateTexture(i);
			texture->Bind();
		}
	}

	VAO->Bind();
	VAO->DrawElements(EBO->GetCount());
	VAO->Unbind();
}
