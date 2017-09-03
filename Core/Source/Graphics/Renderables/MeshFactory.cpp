#include "MeshFactory.h"
#include "Mesh.h"
#include "System/Log.h"
#include "Graphics/Structures/VertexData.h"
#include "System/DeleteMacros.h"
#include "Graphics/Textures/Texture2D.h"

using namespace s3dge;

uint* Get24CubeElements()
{
	int offset = 0;
	uint*const elements = new uint[36];

	for (int i = 0; i < 36; i += 6)
	{
		elements[i + 0] = 0 + offset;
		elements[i + 1] = 1 + offset;
		elements[i + 2] = 2 + offset;
		elements[i + 3] = 2 + offset;
		elements[i + 4] = 3 + offset;
		elements[i + 5] = 0 + offset;
		offset += 4;
	}

	return elements;
}

static void AssignVertexData(VertexData& vertex, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv);

Mesh*const MeshFactory::CreateMesh(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, id*const textures, const uint textureCount)
{
	return new Mesh(vertices, vertexCount, elements, elementCount, textures, textureCount);
}

Mesh*const MeshFactory::CreateCubeOfUnitSize(Texture2D*const texture)
{
	const int vertexCount = 24;
	VertexData* vertexData = new VertexData[vertexCount];

	// front face
	Vector3 frontNormal(0, 0, 1);
	AssignVertexData(vertexData[0], Vector3(0, 0, 1), 0xffffffff, frontNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[1], Vector3(0, 1, 1), 0xffffffff, frontNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[2], Vector3(1, 1, 1), 0xffffffff, frontNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[3], Vector3(1, 0, 1), 0xffffffff, frontNormal, Vector2(1.0f, 0.0f));

	// back face
	Vector3 backNormal(0, 0, -1);
	AssignVertexData(vertexData[4], Vector3(1, 0, 0), 0xffffffff, backNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[5], Vector3(1, 1, 0), 0xffffffff, backNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[6], Vector3(0, 1, 0), 0xffffffff, backNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[7], Vector3(0, 0, 0), 0xffffffff, backNormal, Vector2(1.0f, 0.0f));

	// top face
	Vector3 topNormal(0, 1, 0);
	AssignVertexData(vertexData[8], Vector3(0, 1, 1), 0xffffffff, topNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[9], Vector3(0, 1, 0), 0xffffffff, topNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[10], Vector3(1, 1, 0), 0xffffffff, topNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[11], Vector3(1, 1, 1), 0xffffffff, topNormal, Vector2(1.0f, 0.0f));

	// bottom face
	Vector3 bottomNormal(0, -1, 0);
	AssignVertexData(vertexData[12], Vector3(0, 0, 1), 0xffffffff, bottomNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[13], Vector3(0, 0, 0), 0xffffffff, bottomNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[14], Vector3(1, 0, 0), 0xffffffff, bottomNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[15], Vector3(1, 0, 1), 0xffffffff, bottomNormal, Vector2(1.0f, 0.0f));

	// left face
	Vector3 leftNormal(-1, 0, 0);
	AssignVertexData(vertexData[16], Vector3(0, 0, 0), 0xffffffff, leftNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[17], Vector3(0, 1, 0), 0xffffffff, leftNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[18], Vector3(0, 1, 1), 0xffffffff, leftNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[19], Vector3(0, 0, 1), 0xffffffff, leftNormal, Vector2(1.0f, 0.0f));

	// right face
	Vector3 rightNormal(1, 0, 0);
	AssignVertexData(vertexData[20], Vector3(1, 0, 1), 0xffffffff, rightNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[21], Vector3(1, 1, 1), 0xffffffff, rightNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[22], Vector3(1, 1, 0), 0xffffffff, rightNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[23], Vector3(1, 0, 0), 0xffffffff, rightNormal, Vector2(1.0f, 0.0f));

	uint* elements = Get24CubeElements();

	if (texture)
	{
		uint tex = texture->GetID();
		uint* tex1 = &tex;

		Mesh*const mesh = new Mesh(vertexData, vertexCount, elements, 36, tex1, 1);
		SafeDeleteArray(elements);
		return mesh;
	}
	else
	{
		Mesh*const mesh = new Mesh(vertexData, vertexCount, elements, 36);
		SafeDeleteArray(elements);
		return mesh;
	}
}

static void AssignVertexData(VertexData& vertex, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv)
{
	vertex.Position = position;
	vertex.Color = Color(color);
	vertex.Normal = normal;
	vertex.UV = uv;
}