#include "Cube.h"
#include "System/MemoryManagement.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

using namespace s3dge;

static VertexData* GetCubeVertices(const uint color);
static uint* GetCubeIndices();
static void AddVertex(VertexData*const vertices, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv);

Cube::Cube()
{
	GenerateCube(0xffffff);
}

Cube::Cube(const uint color)
{
	GenerateCube(color);
}

Cube::~Cube()
{
	SafeDelete(VBO);
	SafeDelete(IBO);
}

void Cube::GenerateCube(const uint color)
{
	VertexData* vertices = GetCubeVertices(color);
	VBO = new VertexBuffer(sizeof(VertexData), 24, VertexLayout::GetDefaultMeshVertexLayout(), vertices);
	SafeDeleteArray(vertices);

	uint* indices = GetCubeIndices();
	IBO = new IndexBuffer(36, indices);
	SafeDeleteArray(indices);
}

VertexData* GetCubeVertices(const uint color)
{
	VertexData* vertices = new VertexData[24];

	VertexData* currentVertex = vertices;

	// back face
	Vector3 backNormal(0, 0, -1);
	AddVertex(currentVertex++, Vector3(1, 0, -1), color, backNormal, Vector2(0.0f, 0.0f));
	AddVertex(currentVertex++, Vector3(1, 1, -1), color, backNormal, Vector2(0.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(0, 1, -1), color, backNormal, Vector2(1.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(0, 0, -1), color, backNormal, Vector2(1.0f, 0.0f));

	// front face
	Vector3 frontNormal(0, 0, 1);
	AddVertex(currentVertex++, Vector3(0, 0, 0), color, frontNormal, Vector2(0.0f, 0.0f));
	AddVertex(currentVertex++, Vector3(0, 1, 0), color, frontNormal, Vector2(0.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(1, 1, 0), color, frontNormal, Vector2(1.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(1, 0, 0), color, frontNormal, Vector2(1.0f, 0.0f));

	// top face
	Vector3 topNormal(0, 1, 0);
	AddVertex(currentVertex++, Vector3(0, 1, 0), color, topNormal, Vector2(0.0f, 0.0f));
	AddVertex(currentVertex++, Vector3(0, 1, -1), color, topNormal, Vector2(0.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(1, 1, -1), color, topNormal, Vector2(1.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(1, 1, 0), color, topNormal, Vector2(1.0f, 0.0f));

	// bottom face
	Vector3 bottomNormal(0, -1, 0);
	AddVertex(currentVertex++, Vector3(1, 0, 0), color, bottomNormal, Vector2(0.0f, 0.0f));
	AddVertex(currentVertex++, Vector3(1, 0, -1), color, bottomNormal, Vector2(0.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(0, 0, -1), color, bottomNormal, Vector2(1.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(0, 0, 0), color, bottomNormal, Vector2(1.0f, 0.0f));

	// left face
	Vector3 leftNormal(-1, 0, 0);
	AddVertex(currentVertex++, Vector3(0, 0, -1), color, leftNormal, Vector2(0.0f, 0.0f));
	AddVertex(currentVertex++, Vector3(0, 1, -1), color, leftNormal, Vector2(0.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(0, 1, 0), color, leftNormal, Vector2(1.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(0, 0, 0), color, leftNormal, Vector2(1.0f, 0.0f));

	// right face
	Vector3 rightNormal(1, 0, 0);
	AddVertex(currentVertex++, Vector3(1, 0, 0), 0xffffffff, rightNormal, Vector2(0.0f, 0.0f));
	AddVertex(currentVertex++, Vector3(1, 1, 0), 0xffffffff, rightNormal, Vector2(0.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(1, 1, -1), 0xffffffff, rightNormal, Vector2(1.0f, 1.0f));
	AddVertex(currentVertex++, Vector3(1, 0, -1), 0xffffffff, rightNormal, Vector2(1.0f, 0.0f));

	return vertices;
}

uint* GetCubeIndices()
{
	const int indexCount = 36;
	int offset = 0;
	uint* indices = new uint[indexCount];

	for (int i = 0; i < indexCount; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 2 + offset;
		indices[i + 2] = 1 + offset;
		indices[i + 3] = 0 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 2 + offset;
		offset += 4;
	}

	return indices;
}

static void AddVertex(VertexData*const vertex, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv)
{
	vertex->Position = position;
	vertex->Color = Color(color);
	vertex->Normal = normal;
	vertex->UV = uv;
}