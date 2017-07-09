#include "Logic.h"

using namespace s3dge;

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

	Mesh* mesh = MeshFactory::CreateMesh(vertexData, 8, elements, 36);

	return mesh;
}