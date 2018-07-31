/*
===========================================================================
Mesh.cpp

Implemlents the Mesh class
===========================================================================
*/

#include "Mesh.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Structures/VertexData.h"
#include "System/MemoryManagement.h"
#include "Graphics/AssetManagers/TextureManager.h"
#include "System/Logger.h"
#include "Graphics/GraphicsAPI.h"

using namespace std;
using namespace s3dge;

Mesh::Mesh(const char*const name,
	vector<VertexData> vertices,
	vector<uint> elements,
	vector<Texture2D*> diffTextures,
	vector<Texture2D*> specTextures)
	: Name(name), DiffTextures(diffTextures), SpecTextures(specTextures)
{
	VBO = new VertexBuffer(sizeof(VertexData), vertices.size(), VertexLayout::GetDefaultMeshVertexLayout(), vertices.data());
	IBO = new IndexBuffer(elements.size(), elements.data());
}

Mesh::~Mesh()
{
	SafeDelete(VBO);
	SafeDelete(IBO);

	for (auto texture : DiffTextures)
		SafeDelete(texture);

	for (auto texture : SpecTextures)
		SafeDelete(texture);
}

void Mesh::Draw() const
{
	if (DiffTextures.size() > 1)
		LOG_ERROR("Diff texture count exceeds 1!");

	for (uint i = 0; i < DiffTextures.size(); i++)
	{
		const auto texture = DiffTextures[i];

		Texture2D::ActivateTexture(i);
		texture->Bind();
	}

	if (SpecTextures.size() > 1)
		LOG_ERROR("Spec texture count exceeds 1!");

	const int specOffset = 1; // TODO: remove this.
	for (uint i = 0; i < SpecTextures.size(); i++)
	{
		const auto texture = SpecTextures[i];

		Texture2D::ActivateTexture(i + specOffset);
		texture->Bind();
	}

	Renderable3D::Draw();

	for (uint i = 0; i < SpecTextures.size(); i++)
		SpecTextures[i]->Unbind();
}