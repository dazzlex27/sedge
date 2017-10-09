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
#include "System/Log.h"

using namespace s3dge;

Mesh::Mesh(
	VertexData*const vertices, const uint vertexCount, 
	uint*const elements, const uint elementCount, 
	ID*const diffTextures, const uint diffTexCount,
	ID*const specTextures, const uint specTexCount)
	: DiffTexCount(diffTexCount), SpecTexCount(specTexCount)
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

	if (diffTextures && diffTexCount > 0)
	{
		DiffTextures = new ID[diffTexCount];
		memcpy(DiffTextures, diffTextures, sizeof(ID) * diffTexCount);
	}

	if (specTextures && specTexCount > 0)
	{
		SpecTextures = new ID[specTexCount];
		memcpy(SpecTextures, specTextures, sizeof(ID) * specTexCount);
	}
}

Mesh::~Mesh()
{
	SafeDelete(VAO);
	SafeDelete(VBO);
	SafeDelete(EBO);

	if (DiffTexCount > 0 && DiffTextures)
		SafeDeleteArray(DiffTextures);

	if (SpecTexCount > 0 && SpecTextures)
		SafeDeleteArray(SpecTextures);
}

void Mesh::Draw() const
{
	if (DiffTexCount > 1)
		LOG_ERROR("Diff texture count exceeds 1!");

	for (uint i = 0; i < DiffTexCount; i++)
	{
		const Texture2D*const texture = TextureManager::GetTex2DByID(DiffTextures[i]);

		if (!texture)
		{
			LOG_ERROR("Failed to read diff texture with ID", DiffTextures[i]);
			continue;
		}

		auto texType = texture->GetType();

		Texture2D::ActivateTexture(i);
		texture->Bind();
	}

	if (SpecTexCount > 1)
		LOG_ERROR("Spec texture count exceeds 1!");

	const int specOffset = 1; // TODO: remove this.
	for (uint i = 0; i < SpecTexCount; i++)
	{
		const Texture2D*const texture = TextureManager::GetTex2DByID(SpecTextures[i]);

		if (!texture)
		{
			LOG_ERROR("Failed to read diff texture with ID", SpecTextures[i]);
			continue;
		}

		auto texType = texture->GetType();

		Texture2D::ActivateTexture(i + specOffset);
		texture->Bind();
	}

	VAO->Bind();
	VAO->DrawElements(EBO->GetCount());
	VAO->Unbind();

	for (int i = 0; i < SpecTexCount; i++)
	{
		const Texture2D*const texture = TextureManager::GetTex2DByID(SpecTextures[i]);
		texture->Unbind();
	}
}