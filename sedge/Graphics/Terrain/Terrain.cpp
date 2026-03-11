#include "Terrain.h"
#include "System/MemoryManagement.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/GraphicsAPI.h"
#include "Graphics/Textures/Texture2D.h"

using namespace sedge;

const int MAX_TILES = 1048576;

static uint* FillIndexBuffer(const uint maxIndices);

Terrain::Terrain(Texture2D*const texture)
	: _texture(texture)
{
	GenerateTerrain();
}

Terrain::~Terrain()
{
	SafeDelete(_vbo);
	SafeDelete(_ibo);
}

void Terrain::Draw() const
{
	Texture2D::ActivateTexture(0);
	_texture->Bind();
	_vbo->Bind();
	_ibo->Bind();
	GraphicsAPI::DrawTrianglesIndexed(_ibo->GetCount());
}

void Terrain::GenerateTerrain()
{
	const int vertexCount = MAX_TILES * 4;
	VertexDataTerrain* vertices = new VertexDataTerrain[vertexCount];
	const int indexCount = (int)(vertexCount * 1.5);

	float quarterSize = (float)(sqrt(MAX_TILES) / 2);

	VertexDataTerrain* vertex = vertices;

	for (float z = -quarterSize + 1; z <= quarterSize; z++)
	{
		for (float x = -quarterSize + 1; x <= quarterSize; x++)
		{
			vertex->Position = Vector3(x - 1, 0, z);
			vertex->UV = Vector2(0, 0);
			vertex++;

			vertex->Position = Vector3(x - 1, 0, z + 1);
			vertex->UV = Vector2(0, 1);
			vertex++;

			vertex->Position = Vector3(x, 0, z + 1);
			vertex->UV = Vector2(1, 1);
			vertex++;

			vertex->Position = Vector3(x, 0, z);
			vertex->UV = Vector2(1, 0);
			vertex++;
		}
	}

	_vbo = new VertexBuffer(sizeof(VertexDataTerrain), vertexCount, VertexLayout::GetDefaultTerrainVertexLayout(), vertices);
	SafeDeleteArray(vertices);

	uint* indices = FillIndexBuffer(indexCount);
	_ibo = new IndexBuffer(indexCount, indices);
	SafeDeleteArray(indices);
}

uint* FillIndexBuffer(const uint maxIndices)
{
	uint* indices = new uint[maxIndices];

	for (uint i = 0, offset = 0; i < maxIndices; i += 6, offset += 4)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;
	}

	return indices;
}