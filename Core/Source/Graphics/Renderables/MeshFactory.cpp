#include "MeshFactory.h"
#include "Mesh.h"
#include "System/Log.h"
#include "Graphics/Structures/VertexData.h"
#include "System/DeleteMacros.h"
#include "Graphics/Textures/Texture2D.h"

using namespace std;
using namespace s3dge;

vector<uint> Get24CubeElements()
{
	const int numElements = 36;
	int offset = 0;
	vector<uint>  elements;
	elements.emplace_back(numElements);

	for (int i = 0; i < numElements; i += 6)
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

static void AddVertex(vector<VertexData>& vertices, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv);

Mesh*const MeshFactory::CreateMesh(const char*const name,
	vector<VertexData> vertices,
	vector<uint> elements,
	vector<Texture2D*> diffTextures,
	vector<Texture2D*> specTextures)
{
	return new Mesh(name, vertices, elements, diffTextures, specTextures);
}

Mesh*const MeshFactory::CreateCubeOfUnitSize(Texture2D*const texture)
{
	const int vertexCount = 24;
	vector<VertexData> vertices;
	vertices.reserve(24);

	// front face
	Vector3 frontNormal(0, 0, 1);
	AddVertex(vertices, Vector3(0, 0, 1), 0xffffffff, frontNormal, Vector2(0.0f, 0.0f));
	AddVertex(vertices, Vector3(0, 1, 1), 0xffffffff, frontNormal, Vector2(0.0f, 1.0f));
	AddVertex(vertices, Vector3(1, 1, 1), 0xffffffff, frontNormal, Vector2(1.0f, 1.0f));
	AddVertex(vertices, Vector3(1, 0, 1), 0xffffffff, frontNormal, Vector2(1.0f, 0.0f));

	// back face
	Vector3 backNormal(0, 0, -1);
	AddVertex(vertices, Vector3(1, 0, 0), 0xffffffff, backNormal, Vector2(0.0f, 0.0f));
	AddVertex(vertices, Vector3(1, 1, 0), 0xffffffff, backNormal, Vector2(0.0f, 1.0f));
	AddVertex(vertices, Vector3(0, 1, 0), 0xffffffff, backNormal, Vector2(1.0f, 1.0f));
	AddVertex(vertices, Vector3(0, 0, 0), 0xffffffff, backNormal, Vector2(1.0f, 0.0f));

	// top face
	Vector3 topNormal(0, 1, 0);
	AddVertex(vertices, Vector3(0, 1, 1), 0xffffffff, topNormal, Vector2(0.0f, 0.0f));
	AddVertex(vertices, Vector3(0, 1, 0), 0xffffffff, topNormal, Vector2(0.0f, 1.0f));
	AddVertex(vertices, Vector3(1, 1, 0), 0xffffffff, topNormal, Vector2(1.0f, 1.0f));
	AddVertex(vertices, Vector3(1, 1, 1), 0xffffffff, topNormal, Vector2(1.0f, 0.0f));

	// bottom face
	Vector3 bottomNormal(0, -1, 0);
	AddVertex(vertices, Vector3(0, 0, 1), 0xffffffff, bottomNormal, Vector2(0.0f, 0.0f));
	AddVertex(vertices, Vector3(0, 0, 0), 0xffffffff, bottomNormal, Vector2(0.0f, 1.0f));
	AddVertex(vertices, Vector3(1, 0, 0), 0xffffffff, bottomNormal, Vector2(1.0f, 1.0f));
	AddVertex(vertices, Vector3(1, 0, 1), 0xffffffff, bottomNormal, Vector2(1.0f, 0.0f));

	// left face
	Vector3 leftNormal(-1, 0, 0);
	AddVertex(vertices, Vector3(0, 0, 0), 0xffffffff, leftNormal, Vector2(0.0f, 0.0f));
	AddVertex(vertices, Vector3(0, 1, 0), 0xffffffff, leftNormal, Vector2(0.0f, 1.0f));
	AddVertex(vertices, Vector3(0, 1, 1), 0xffffffff, leftNormal, Vector2(1.0f, 1.0f));
	AddVertex(vertices, Vector3(0, 0, 1), 0xffffffff, leftNormal, Vector2(1.0f, 0.0f));

	// right face
	Vector3 rightNormal(1, 0, 0);
	AddVertex(vertices, Vector3(1, 0, 1), 0xffffffff, rightNormal, Vector2(0.0f, 0.0f));
	AddVertex(vertices, Vector3(1, 1, 1), 0xffffffff, rightNormal, Vector2(0.0f, 1.0f));
	AddVertex(vertices, Vector3(1, 1, 0), 0xffffffff, rightNormal, Vector2(1.0f, 1.0f));
	AddVertex(vertices, Vector3(1, 0, 0), 0xffffffff, rightNormal, Vector2(1.0f, 0.0f));

	vector<uint> elements = Get24CubeElements();

	vector<Texture2D*> textures;
	textures.reserve(1);
	textures.emplace_back(texture);

	if (texture)
	{
		Mesh*const mesh = new Mesh("", vertices, elements, textures);
		return mesh;
	}
	else
	{
		Mesh*const mesh = new Mesh("", vertices, elements);
		return mesh;
	}

	return nullptr;
}

static void AddVertex(vector<VertexData>& vertices, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv)
{
	VertexData vertex;
	vertex.Position = position;
	vertex.Color = Color(color);
	vertex.Normal = normal;
	vertex.UV = uv;

	vertices.emplace_back(vertex);
}