#include "Logic.h"

using namespace s3dge;

uint* Cube8ElementArray = nullptr;
uint* Cube24ElementArray = nullptr;

uint* CreateCube8ElementArray()
{
	uint* elements = new uint[36];

	elements[0] = 0;
	elements[1] = 1;
	elements[2] = 2;
	elements[3] = 2;
	elements[4] = 3;
	elements[5] = 0;
	elements[6] = 1;
	elements[7] = 5;
	elements[8] = 6;
	elements[9] = 6;
	elements[10] = 2;
	elements[11] = 1;
	elements[12] = 7;
	elements[13] = 6;
	elements[14] = 5;
	elements[15] = 5;
	elements[16] = 4;
	elements[17] = 7;
	elements[18] = 4;
	elements[19] = 0;
	elements[20] = 3;
	elements[21] = 3;
	elements[22] = 7;
	elements[23] = 4;
	elements[24] = 4;
	elements[25] = 5;
	elements[26] = 1;
	elements[27] = 1;
	elements[28] = 0;
	elements[29] = 4;
	elements[30] = 3;
	elements[31] = 2;
	elements[32] = 6;
	elements[33] = 6;
	elements[34] = 7;
	elements[35] = 3;

	return elements;
}

uint* CreateCube24ElementArray()
{
	int offset = 0;
	uint* elements = new uint[36];

	for (int i = 0; i < 36; i+=6)
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

uint* GetCube8ElementArray()
{
	if (Cube8ElementArray == nullptr)
		Cube8ElementArray = CreateCube8ElementArray();

	return Cube8ElementArray;
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

	vertexData[0].Position = Point3D(1, 1, -5);
	vertexData[0].Color = Color(0xff00ffff);
	vertexData[0].Normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData[1].Position = Point3D(2, 0.5, -5);
	vertexData[1].Color = Color(0xffff00ff);
	vertexData[1].Normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData[2].Position = Point3D(1, 0, -5);
	vertexData[2].Color = Color(0xffffff00);
	vertexData[2].Normal = Vector3(0.0f, 0.0f, 1.0f);

	uint* elements = new uint[3];
	elements[0] = 0;
	elements[1] = 1;
	elements[2] = 2;

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, 3, elements, 3);

	return mesh;
}

Mesh* CreateRoomMesh()
{
	VertexData* vertexData = new VertexData[8];

	vertexData[0].Position = Point3D(-4, -1, 8);
	vertexData[0].Color = Color(0xf0ff10ff);
	vertexData[1].Position = Point3D(4, -1, 8);
	vertexData[1].Color = Color(0xf0ffff10);
	vertexData[2].Position = Point3D(4, 3, 8);
	vertexData[2].Color = Color(0xf010ffff);
	vertexData[3].Position = Point3D(-4, 3, 8);
	vertexData[3].Color = Color(0xf01010ff);
	vertexData[4].Position = Point3D(-4, -1, -8);
	vertexData[4].Color = Color(0xf0ffffff);
	vertexData[5].Position = Point3D(4, -1, -8);
	vertexData[5].Color = Color(0xf0ff3ff0);
	vertexData[6].Position = Point3D(4, 3, -8);
	vertexData[6].Color = Color(0xf0b0bfff);
	vertexData[7].Position = Point3D(-4, 3, -8);
	vertexData[7].Color = Color(0xf000fa9a);

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, 8, CreateCube8ElementArray(), 36);

	return mesh;
}

void AssignVertexData(VertexData& vertex, const Point3D& position, const uint color, const Vector3& normal, const Point2D& uv)
{
	vertex.Position = position;
	vertex.Color = Color(color);
	vertex.Normal = normal;
	vertex.UV = uv;
}

Mesh* CreateTexturedCube(Texture2D* texture)
{
	int vertexCount = 24;
	VertexData* vertexData = new VertexData[vertexCount];

	// front face
	Vector3 frontNormal(0, 0, -1);
	AssignVertexData(vertexData[0], Point3D(-2, 0, -2.5f), 0xffffffff, frontNormal, Point2D(0.0f, 0.0f));
	AssignVertexData(vertexData[1], Point3D(-2, 1, -2.5f), 0xffffffff, frontNormal, Point2D(0.0f, 1.0f));
	AssignVertexData(vertexData[2], Point3D(-1, 1, -2.5f), 0xffffffff, frontNormal, Point2D(1.0f, 1.0f));
	AssignVertexData(vertexData[3], Point3D(-1, 0, -2.5f), 0xffffffff, frontNormal, Point2D(1.0f, 0.0f));

	// back face
	Vector3 backNormal(0, 0, 1);
	AssignVertexData(vertexData[4], Point3D(-1, 0, -1.5f), 0xffffffff, backNormal, Point2D(0.0f, 0.0f));
	AssignVertexData(vertexData[5], Point3D(-1, 1, -1.5f), 0xffffffff, backNormal, Point2D(0.0f, 1.0f));
	AssignVertexData(vertexData[6], Point3D(-2, 1, -1.5f), 0xffffffff, backNormal, Point2D(1.0f, 1.0f));
	AssignVertexData(vertexData[7], Point3D(-2, 0, -1.5f), 0xffffffff, backNormal, Point2D(1.0f, 0.0f));

	// top face
	Vector3 topNormal(0, 1, 0);
	AssignVertexData(vertexData[8], Point3D(-2, 1, -2.5f), 0xffffffff, topNormal, Point2D(0.0f, 0.0f));
	AssignVertexData(vertexData[9], Point3D(-2, 1, -1.5f), 0xffffffff, topNormal, Point2D(0.0f, 1.0f));
	AssignVertexData(vertexData[10], Point3D(-1, 1, -1.5f), 0xffffffff, topNormal, Point2D(1.0f, 1.0f));
	AssignVertexData(vertexData[11], Point3D(-1, 1, -2.5f), 0xffffffff, topNormal, Point2D(1.0f, 0.0f));

	// bottom face
	Vector3 bottomNormal(0, -1, 0);
	AssignVertexData(vertexData[12], Point3D(-2, 0, -1.5f), 0xffffffff, bottomNormal, Point2D(0.0f, 0.0f));
	AssignVertexData(vertexData[13], Point3D(-2, 0, -2.5f), 0xffffffff, bottomNormal, Point2D(0.0f, 1.0f));
	AssignVertexData(vertexData[14], Point3D(-1, 0, -2.5f), 0xffffffff, bottomNormal, Point2D(1.0f, 1.0f));
	AssignVertexData(vertexData[15], Point3D(-1, 0, -1.5f), 0xffffffff, bottomNormal, Point2D(1.0f, 0.0f));

	// left face
	Vector3 leftNormal(-1, 0, 0);
	AssignVertexData(vertexData[16], Point3D(-2, 0, -2.5f), 0xffffffff, leftNormal, Point2D(0.0f, 0.0f));
	AssignVertexData(vertexData[17], Point3D(-2, 1, -2.5f), 0xffffffff, leftNormal, Point2D(0.0f, 1.0f));
	AssignVertexData(vertexData[18], Point3D(-2, 1, -1.5f), 0xffffffff, leftNormal, Point2D(1.0f, 1.0f));
	AssignVertexData(vertexData[19], Point3D(-2, 0, -1.5f), 0xffffffff, leftNormal, Point2D(1.0f, 0.0f));

	// right face
	Vector3 rightNormal(1, 0, 0);
	AssignVertexData(vertexData[20], Point3D(-1, 0, -1.5f), 0xffffffff, rightNormal, Point2D(0.0f, 0.0f));
	AssignVertexData(vertexData[21], Point3D(-1, 1, -1.5f), 0xffffffff, rightNormal, Point2D(0.0f, 1.0f));
	AssignVertexData(vertexData[22], Point3D(-1, 1, -2.5f), 0xffffffff, rightNormal, Point2D(1.0f, 1.0f));
	AssignVertexData(vertexData[23], Point3D(-1, 0, -2.5f), 0xffffffff, rightNormal, Point2D(1.0f, 0.0f));

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, vertexCount, CreateCube24ElementArray(), 36, texture);

	return mesh;
}

//Mesh* CreateTexturedCube(Texture2D* texture)
//{
//	VertexData* vertexData = new VertexData[8];
//
//	vertexData[0].Position = Point3D(-2, 0, -2.5f);	// left bottom front
//	vertexData[0].Color = Color(0xffffffff);		//
//	vertexData[0].Normal = Vector3(-0.5f, -0.5f, -0.5f);
//	vertexData[0].UV = Point2D(0.0f, 1.0f);
//	vertexData[1].Position = Point3D(-1, 0, -2.5f);	// right bottom front 
//	vertexData[1].Color = Color(0xffffffff);		// 
//	vertexData[1].Normal = Vector3(0.5f, -0.5f, -0.5f);
//	vertexData[1].UV = Point2D(1.0f, 1.0f);
//	vertexData[2].Position = Point3D(-1, 1, -2.5f);	// right top font
//	vertexData[2].Color = Color(0xffffffff);		//
//	vertexData[2].Normal = Vector3(0.5f, 0.5f, -0.5f);
//	vertexData[2].UV = Point2D(1.0f, 0.0f);
//	vertexData[3].Position = Point3D(-2, 1, -2.5f);	// left top front
//	vertexData[3].Color = Color(0xffffffff);		//
//	vertexData[3].Normal = Vector3(-0.5f, 0.5f, -0.5f);
//	vertexData[3].UV = Point2D(0.0f, 0.0f);
//	vertexData[4].Position = Point3D(-2, 0, -1.5f);	// left bottom back
//	vertexData[4].Color = Color(0xffffffff);		//
//	vertexData[4].Normal = Vector3(-0.5f, -0.5f, 0.5f);
//	vertexData[4].UV = Point2D(0.0f, 0.0f);
//	vertexData[5].Position = Point3D(-1, 0, -1.5f);	// right bottom back
//	vertexData[5].Color = Color(0xffffffff);		//
//	vertexData[5].Normal = Vector3(0.5f, -0.5f, 0.5f);
//	vertexData[5].UV = Point2D(1.0f, 0.0f);
//	vertexData[6].Position = Point3D(-1, 1, -1.5f);	// right top back
//	vertexData[6].Color = Color(0xffffffff);		//
//	vertexData[6].Normal = Vector3(0.5f, 0.5f, 0.5f);
//	vertexData[6].UV = Point2D(1.0f, 1.0f);
//	vertexData[7].Position = Point3D(-2, 1, -1.5f);	// left top back
//	vertexData[7].Color = Color(0xffffffff);		//
//	vertexData[7].Normal = Vector3(-0.5f, 0.5f, 0.5f);
//	vertexData[7].UV = Point2D(0.0f, 1.0f);
//
//	Mesh* mesh = MeshFactory::CreateMesh(vertexData, 8, GetCubeElementArray(), 36, texture);
//
//	return mesh;
//}

//uint* CreateCubeElementArray()
//{
//	uint* elements = new uint[36];
//
//	elements[0] = 0;
//	elements[1] = 1;
//	elements[2] = 2;
//	elements[3] = 2;
//	elements[4] = 3;
//	elements[5] = 0;
//	elements[6] = 1;
//	elements[7] = 5;
//	elements[8] = 6;
//	elements[9] = 6;
//	elements[10] = 2;
//	elements[11] = 1;
//	elements[12] = 7;
//	elements[13] = 6;
//	elements[14] = 5;
//	elements[15] = 5;
//	elements[16] = 4;
//	elements[17] = 7;
//	elements[18] = 4;
//	elements[19] = 0;
//	elements[20] = 3;
//	elements[21] = 3;
//	elements[22] = 7;
//	elements[23] = 4;
//	elements[24] = 4;
//	elements[25] = 5;
//	elements[26] = 1;
//	elements[27] = 1;
//	elements[28] = 0;
//	elements[29] = 4;
//	elements[30] = 3;
//	elements[31] = 2;
//	elements[32] = 6;
//	elements[33] = 6;
//	elements[34] = 7;
//	elements[35] = 3;
//
//	return elements;
//}