#include "MeshFactory.h"
#include "Mesh.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Structures/VertexData.h"
#include "Math/Size3D.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;

Mesh*const MeshFactory::CreateMesh(VertexData*const vertices, const uint vertexCount, uint*const elements, const uint elementCount, Texture2D*const texture)
{
	Mesh*const mesh = new Mesh(vertices, vertexCount, elements, elementCount, texture);

	return mesh;
}

Mesh*const MeshFactory::CreateCuboid(const Size3D& size, Texture2D*const texture, const DrawingMode drawingMode)
{
	return nullptr;
}

Mesh*const MeshFactory::CreateCuboid(const Size3D& size, const Color& color, const DrawingMode drawingMode)
{
	const float hw = size.width / 2;
	const float hy = size.height / 2;
	const float hz = size.depth / 2;

	VertexData* vertexData = new VertexData[8];

	vertexData[0].Position = Vector3(-hw, -hy, hz);
	vertexData[0].Color = Color(0xffffff00);
	vertexData[1].Position = Vector3(hw, -hy, hz);
	vertexData[1].Color = Color(0xffffff00);
	vertexData[2].Position = Vector3(hw, hy, hz);
	vertexData[2].Color = Color(0xffffff00);
	vertexData[3].Position = Vector3(-hw, hy, hz);
	vertexData[3].Color = Color(0xffffff00);
	vertexData[4].Position = Vector3(-hw, -hy, -hz);
	vertexData[4].Color = Color(0xffffff00);
	vertexData[5].Position = Vector3(hw, -hy, -hz);
	vertexData[5].Color = Color(0xffffff00);
	vertexData[6].Position = Vector3(hw, hy, -hz);
	vertexData[6].Color = Color(0xffffff00);
	vertexData[7].Position = Vector3(-hw, hy, -hz);
	vertexData[7].Color = Color(0xffffff00);

	uint elements[] =
	{
		0,  1,  2,  0,  2,  3,   //front
		4,  5,  6,  4,  6,  7,   //right
		8,  9,  10, 8,  10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23   //bottom
	};

	Mesh*const mesh = new Mesh(vertexData, 8, elements, 36);

	SafeDeleteArray(vertexData);

	return mesh;
}

Mesh*const MeshFactory::CreateCube(const float size, Texture2D*const texture, const DrawingMode drawingMode)
{
	const float h = size / 2;

	VertexData* vertexData = new VertexData[8];

	vertexData[0].Position = Vector3(-h, -h, h);
	vertexData[0].Color = Color(0xffffff00);
	vertexData[1].Position = Vector3(h, -h, h);
	vertexData[1].Color = Color(0xffffff00);
	vertexData[2].Position = Vector3(h, h, h);
	vertexData[2].Color = Color(0xffffff00);
	vertexData[3].Position = Vector3(-h, h, h);
	vertexData[3].Color = Color(0xffffff00);
	vertexData[4].Position = Vector3(-h, -h, -h);
	vertexData[4].Color = Color(0xffffff00);
	vertexData[5].Position = Vector3(h, -h, -h);
	vertexData[5].Color = Color(0xffffff00);
	vertexData[6].Position = Vector3(h, h, -h);
	vertexData[6].Color = Color(0xffffff00);
	vertexData[7].Position = Vector3(-h, h, -h);
	vertexData[7].Color = Color(0xffffff00);

	uint elements[] =
	{
		0,  1,  2,  0,  2,  3,   //front
		4,  5,  6,  4,  6,  7,   //right
		8,  9,  10, 8,  10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23   //bottom
	};

	Mesh*const mesh = new Mesh(vertexData, 8, elements, 36);

	SafeDeleteArray(vertexData);

	return mesh;
}

Mesh*const MeshFactory::CreateCube(const float size, const Color& color, const DrawingMode drawingMode)
{
	const float h = size / 2;

	VertexData* vertexData = new VertexData[8];

	vertexData[0].Position = Vector3(-h, -h, h);
	vertexData[0].Color = color;
	vertexData[1].Position = Vector3(h, -h, h);
	vertexData[1].Color = color;
	vertexData[2].Position = Vector3(h, h, h);
	vertexData[2].Color = color;
	vertexData[3].Position = Vector3(-h, h, h);
	vertexData[3].Color = color;
	vertexData[4].Position = Vector3(-h, -h, -h);
	vertexData[4].Color = color;
	vertexData[5].Position = Vector3(h, -h, -h);
	vertexData[5].Color = color;
	vertexData[6].Position = Vector3(h, h, -h);
	vertexData[6].Color = color;
	vertexData[7].Position = Vector3(-h, h, -h);
	vertexData[7].Color = color;

	uint elements[] =
	{
		0,  1,  2,  0,  2,  3,   //front
		4,  5,  6,  4,  6,  7,   //right
		8,  9,  10, 8,  10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23   //bottom
	};

	Mesh*const mesh = new Mesh(vertexData, 8, elements, 36);

	SafeDeleteArray(vertexData);

	return mesh;
}
