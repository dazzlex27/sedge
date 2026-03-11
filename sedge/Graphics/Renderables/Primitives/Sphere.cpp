#include "Sphere.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/GraphicsAPI.h"
#include "System/MemoryManagement.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Structures/VertexLayout.h"

using namespace sedge;

static VertexData* GetSphereVertices(const uint color);
static uint* GetSphereIndices();
static void AddVertex(VertexData*const vertices, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv);

Shpere::Shpere()
{
	GenerateSphere(0xffffff);
}

Shpere::Shpere(const uint color)
{
	GenerateSphere(color);
}

Shpere::~Shpere()
{
	SafeDelete(VBO);
	SafeDelete(IBO);
}

void Shpere::GenerateSphere(const uint color)
{
	VertexData* vertices = GetSphereVertices(color);
	VBO = new VertexBuffer(sizeof(VertexData), 24, VertexLayout::GetDefaultMeshVertexLayout(), vertices);
	SafeDeleteArray(vertices);

	uint* indices = GetSphereIndices();
	IBO = new IndexBuffer(36, indices);
	SafeDeleteArray(indices);
}

VertexData* GetSphereVertices(const uint color)
{
	return nullptr;
}

uint* GetSphereIndices()
{
	return nullptr;
}

static void AddVertex(VertexData*const vertex, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv)
{
	vertex->Position = position;
	vertex->Color = Color(color);
	vertex->Normal = normal;
	vertex->UV = uv;
}