#include "Logic.h"

using namespace s3dge;

uint* CubeElementArray = nullptr;

uint* CreateCubeElementArray()
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

uint* GetCubeElementArray()
{
	if (CubeElementArray == nullptr)
		CubeElementArray = CreateCubeElementArray();

	return CubeElementArray;
}

Mesh* CreateArrowMesh()
{
	VertexData* vertexData = new VertexData[3];

	vertexData[0].Position = Point3D(1, 1, -5);
	vertexData[0].Color = Color(0xff00ffff);
	vertexData[1].Position = Point3D(2, 0.5, -5);
	vertexData[1].Color = Color(0xffff00ff);
	vertexData[2].Position = Point3D(1, 0, -5);
	vertexData[2].Color = Color(0xffffff00);

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

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, 8, GetCubeElementArray(), 36);

	return mesh;
}

Mesh* CreateTexturedCube(Texture2D* texture)
{
	VertexData* vertexData = new VertexData[8];

	vertexData[0].Position = Point3D(-2, 0, -2.5f);	// left bottom front
	vertexData[0].Color = Color(0xffffffff);		//
	vertexData[0].UV = Point2D(0.0f, 1.0f);
	vertexData[1].Position = Point3D(-1, 0, -2.5f);	// right bottom front 
	vertexData[1].Color = Color(0xffffffff);		// 
	vertexData[1].UV = Point2D(1.0f, 1.0f);
	vertexData[2].Position = Point3D(-1, 1, -2.5f);	// right top font
	vertexData[2].Color = Color(0xffffffff);		//
	vertexData[2].UV = Point2D(1.0f, 0.0f);
	vertexData[3].Position = Point3D(-2, 1, -2.5f);	// left top front
	vertexData[3].Color = Color(0xffffffff);		//
	vertexData[3].UV = Point2D(0.0f, 0.0f);
	vertexData[4].Position = Point3D(-2, 0, -1.5f);	// left bottom back
	vertexData[4].Color = Color(0xffffffff);		//
	vertexData[4].UV = Point2D(0.0f, 0.0f);
	vertexData[5].Position = Point3D(-1, 0, -1.5f);	// right bottom back
	vertexData[5].Color = Color(0xffffffff);		//
	vertexData[5].UV = Point2D(1.0f, 0.0f);
	vertexData[6].Position = Point3D(-1, 1, -1.5f);	// right top back
	vertexData[6].Color = Color(0xffffffff);		//
	vertexData[6].UV = Point2D(1.0f, 1.0f);
	vertexData[7].Position = Point3D(-2, 1, -1.5f);	// left top back
	vertexData[7].Color = Color(0xffffffff);		//
	vertexData[7].UV = Point2D(0.0f, 1.0f);

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, 8, GetCubeElementArray(), 36, texture);

	return mesh;
}