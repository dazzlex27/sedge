#include "Logic.h"

using namespace s3dge;

uint* QuadElementArray = nullptr;
uint* Cube24ElementArray = nullptr;

uint* CreateQuadElementArray()
{
	uint* elements = new uint[6];

	elements[0] = 0;
	elements[1] = 1;
	elements[2] = 2;
	elements[3] = 2;
	elements[4] = 3;
	elements[5] = 0;

	return elements;
}

uint* CreateCube24ElementArray()
{
	int offset = 0;
	uint* elements = new uint[36];

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

uint* GetQuadElementArray()
{
	if (QuadElementArray == nullptr)
		QuadElementArray = CreateQuadElementArray();

	return QuadElementArray;
}

uint* GetCube24ElementArray()
{
	if (Cube24ElementArray == nullptr)
		Cube24ElementArray = CreateCube24ElementArray();

	return Cube24ElementArray;
}

Mesh* CreateArrowMesh()
{
	VertexData* vertexData = new VertexData[3];

	vertexData[0].Position = Point3D(1, 1, -4);
	vertexData[0].Color = Color(0xff00ffff);
	vertexData[0].Normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData[1].Position = Point3D(2, 0.5, -4);
	vertexData[1].Color = Color(0xffff00ff);
	vertexData[1].Normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData[2].Position = Point3D(1, 0, -4);
	vertexData[2].Color = Color(0xffffff00);
	vertexData[2].Normal = Vector3(0.0f, 0.0f, 1.0f);

	uint* elements = new uint[3];
	elements[0] = 0;
	elements[1] = 1;
	elements[2] = 2;

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, 3, elements, 3);

	return mesh;
}

Mesh* CreateRoomMesh(Texture2D* texture, const float textureNum)
{
	VertexData* vertexData = new VertexData[4];

	vertexData[0].Position = Point3D(-4, 0, 8);
	vertexData[0].Color = Color(0xffffffff);
	vertexData[0].Normal = Vector3(0, 1, 0);
	vertexData[0].UV = Point2D(0.0f, 0.0f);
	vertexData[0].TextureID = textureNum;

	vertexData[1].Position = Point3D(-4, 0, -8);
	vertexData[1].Color = Color(0xffffffff);
	vertexData[1].Normal = Vector3(0, 1, 0);
	vertexData[1].UV = Point2D(0.0f, 1.0f);
	vertexData[1].TextureID = textureNum;

	vertexData[2].Position = Point3D(4, 0, -8);
	vertexData[2].Color = Color(0xffffffff);
	vertexData[2].Normal = Vector3(0, 1, 0);
	vertexData[2].UV = Point2D(1.0f, 1.0f);
	vertexData[2].TextureID = textureNum;

	vertexData[3].Position = Point3D(4, 0, 8);
	vertexData[3].Color = Color(0xffffffff);
	vertexData[3].Normal = Vector3(0, 1, 0);
	vertexData[3].UV = Point2D(1.0f, 0.0f);
	vertexData[3].TextureID = textureNum;

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, 8, GetQuadElementArray(), 6, texture);

	return mesh;
}

void AssignVertexData(VertexData& vertex, const Point3D& position, const uint color, const Vector3& normal, const Point2D& uv, const float textureID)
{
	vertex.Position = position;
	vertex.Color = Color(color);
	vertex.Normal = normal;
	vertex.UV = uv;
	vertex.TextureID = textureID;
}

Mesh* CreateTexturedCubeUnitSize(Texture2D* texture, const float textureNum)
{
	const int vertexCount = 24;
	VertexData* vertexData = new VertexData[vertexCount];

	// front face
	Vector3 frontNormal(0, 0, -1);
	AssignVertexData(vertexData[0], Point3D(0, 0, 1), 0xffffffff, frontNormal, Point2D(0.0f, 0.0f), textureNum);
	AssignVertexData(vertexData[1], Point3D(0, 1, 1), 0xffffffff, frontNormal, Point2D(0.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[2], Point3D(1, 1, 1), 0xffffffff, frontNormal, Point2D(1.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[3], Point3D(1, 0, 1), 0xffffffff, frontNormal, Point2D(1.0f, 0.0f), textureNum);

	// back face
	Vector3 backNormal(0, 0, 1);
	AssignVertexData(vertexData[4], Point3D(1, 0, 0), 0xffffffff, backNormal, Point2D(0.0f, 0.0f), textureNum);
	AssignVertexData(vertexData[5], Point3D(1, 1, 0), 0xffffffff, backNormal, Point2D(0.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[6], Point3D(0, 1, 0), 0xffffffff, backNormal, Point2D(1.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[7], Point3D(0, 0, 0), 0xffffffff, backNormal, Point2D(1.0f, 0.0f), textureNum);

	// top face
	Vector3 topNormal(0, 1, 0);
	AssignVertexData(vertexData[8], Point3D(0, 1, 1), 0xffffffff, topNormal, Point2D(0.0f, 0.0f), textureNum);
	AssignVertexData(vertexData[9], Point3D(0, 1, 0), 0xffffffff, topNormal, Point2D(0.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[10], Point3D(1, 1, 0), 0xffffffff, topNormal, Point2D(1.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[11], Point3D(1, 1, 1), 0xffffffff, topNormal, Point2D(1.0f, 0.0f), textureNum);

	// bottom face
	Vector3 bottomNormal(0, -1, 0);
	AssignVertexData(vertexData[12], Point3D(0, 0, 1), 0xffffffff, bottomNormal, Point2D(0.0f, 0.0f), textureNum);
	AssignVertexData(vertexData[13], Point3D(0, 0, 0), 0xffffffff, bottomNormal, Point2D(0.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[14], Point3D(1, 0, 0), 0xffffffff, bottomNormal, Point2D(1.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[15], Point3D(1, 0, 1), 0xffffffff, bottomNormal, Point2D(1.0f, 0.0f), textureNum);

	// left face
	Vector3 leftNormal(-1, 0, 0);
	AssignVertexData(vertexData[16], Point3D(0, 0, 0), 0xffffffff, leftNormal, Point2D(0.0f, 0.0f), textureNum);
	AssignVertexData(vertexData[17], Point3D(0, 1, 0), 0xffffffff, leftNormal, Point2D(0.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[18], Point3D(0, 1, 1), 0xffffffff, leftNormal, Point2D(1.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[19], Point3D(0, 0, 1), 0xffffffff, leftNormal, Point2D(1.0f, 0.0f), textureNum);

	// right face
	Vector3 rightNormal(1, 0, 0);
	AssignVertexData(vertexData[20], Point3D(1, 0, 1), 0xffffffff, rightNormal, Point2D(0.0f, 0.0f), textureNum);
	AssignVertexData(vertexData[21], Point3D(1, 1, 1), 0xffffffff, rightNormal, Point2D(0.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[22], Point3D(1, 1, 0), 0xffffffff, rightNormal, Point2D(1.0f, 1.0f), textureNum);
	AssignVertexData(vertexData[23], Point3D(1, 0, 0), 0xffffffff, rightNormal, Point2D(1.0f, 0.0f), textureNum);

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, vertexCount, GetCube24ElementArray(), 36, texture);

	return mesh;
}