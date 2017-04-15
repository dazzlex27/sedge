#include "MeshFactory.h"
#include "Mesh.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Structures/VertexData.h"
#include "Internal/Log.h"
#include "Common/Structures/Point3D.h"
#include "Common/Structures/Size3D.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace graphics;

Mesh* MeshFactory::CreateMesh(VertexBuffer* vbo, IndexBuffer* ibo)
{
	Mesh* mesh = new Mesh(vbo, ibo);

	return mesh;
}

Mesh* MeshFactory::CreateCuboid(const Size3D& size, const Color& color)
{
	float hw = size.width / 2;
	float hy = size.height / 2;
	float hz = size.depth / 2;

	VertexData* vertexData = new VertexData[8];

	vertexData[0].Position = Point3D(-hw, -hy, hz);
	vertexData[0].Color = Color(0xffffff00);
	vertexData[1].Position = Point3D(hw, -hy, hz);
	vertexData[1].Color = Color(0xffffff00);
	vertexData[2].Position = Point3D(hw, hy, hz);
	vertexData[2].Color = Color(0xffffff00);
	vertexData[3].Position = Point3D(-hw, hy, hz);
	vertexData[3].Color = Color(0xffffff00);
	vertexData[4].Position = Point3D(-hw, -hy, -hz);
	vertexData[4].Color = Color(0xffffff00);
	vertexData[5].Position = Point3D(hw, -hy, -hz);
	vertexData[5].Color = Color(0xffffff00);
	vertexData[6].Position = Point3D(hw, hy, -hz);
	vertexData[6].Color = Color(0xffffff00);
	vertexData[7].Position = Point3D(-hw, hy, -hz);
	vertexData[7].Color = Color(0xffffff00);

	VertexBuffer* vbo = new VertexBuffer(vertexData, sizeof(VertexData), 8);

	uint indices[] =
	{
		0,  1,  2,  0,  2,  3,   //front
		4,  5,  6,  4,  6,  7,   //right
		8,  9,  10, 8,  10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23   //bottom
	};
	IndexBuffer* ibo = new IndexBuffer(indices, 36);

	Mesh* mesh = new Mesh(vbo, ibo);

	SafeDeleteArray(vertexData);

	return mesh;
}

Mesh* MeshFactory::CreateCube(float size, Texture2D* texture)
{
	float h = size / 2;

	VertexData* vertexData = new VertexData[8];

	vertexData[0].Position = Point3D(-h, -h, h);
	vertexData[0].Color = Color(0xffffff00);
	vertexData[1].Position = Point3D(h, -h, h);
	vertexData[1].Color = Color(0xffffff00);
	vertexData[2].Position = Point3D(h, h, h);
	vertexData[2].Color = Color(0xffffff00);
	vertexData[3].Position = Point3D(-h, h, h);
	vertexData[3].Color = Color(0xffffff00);
	vertexData[4].Position = Point3D(-h, -h, -h);
	vertexData[4].Color = Color(0xffffff00);
	vertexData[5].Position = Point3D(h, -h, -h);
	vertexData[5].Color = Color(0xffffff00);
	vertexData[6].Position = Point3D(h, h, -h);
	vertexData[6].Color = Color(0xffffff00);
	vertexData[7].Position = Point3D(-h, h, -h);
	vertexData[7].Color = Color(0xffffff00);

	VertexBuffer* vbo = new VertexBuffer(vertexData, sizeof(VertexData), 8);

	uint indices[] =
	{
		0,  1,  2,  0,  2,  3,   //front
		4,  5,  6,  4,  6,  7,   //right
		8,  9,  10, 8,  10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23   //bottom
	};
	IndexBuffer* ibo = new IndexBuffer(indices, 36);

	Mesh* mesh = new Mesh(vbo, ibo, texture);

	SafeDeleteArray(vertexData);

	return mesh;
}

Mesh* MeshFactory::CreateCube(float size, const Color& color)
{
	float h = size / 2;

	VertexData* vertexData = new VertexData[8];

	vertexData[0].Position = Point3D(-h, -h, h);
	vertexData[0].Color = color;
	vertexData[1].Position = Point3D(h, -h, h);
	vertexData[1].Color = color;
	vertexData[2].Position = Point3D(h, h, h);
	vertexData[2].Color = color;
	vertexData[3].Position = Point3D(-h, h, h);
	vertexData[3].Color = color;
	vertexData[4].Position = Point3D(-h, -h, -h);
	vertexData[4].Color = color;
	vertexData[5].Position = Point3D(h, -h, -h);
	vertexData[5].Color = color;
	vertexData[6].Position = Point3D(h, h, -h);
	vertexData[6].Color = color;
	vertexData[7].Position = Point3D(-h, h, -h);
	vertexData[7].Color = color;

	VertexBuffer* vbo = new VertexBuffer(vertexData, sizeof(VertexData), 8);

	uint indices[] =
	{
		0,  1,  2,  0,  2,  3,   //front
		4,  5,  6,  4,  6,  7,   //right
		8,  9,  10, 8,  10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23   //bottom
	};
	IndexBuffer* ibo = new IndexBuffer(indices, 36);

	Mesh* mesh = new Mesh(vbo, ibo);

	SafeDeleteArray(vertexData);

	return mesh;
}
