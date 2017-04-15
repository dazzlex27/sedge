#include "MeshFactory.h"
#include "Mesh.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Structures/VertexData.h"
#include "Internal/Log.h"
#include "Common/Structures/Point3D.h"
#include "Common/Structures/Size3D.h"

using namespace s3dge;
using namespace graphics;

Mesh* MeshFactory::CreateMesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, Texture2D* texture)
{
	Mesh* mesh = new Mesh(vertexBuffer, indexBuffer, texture);

	return mesh;
}

Mesh* MeshFactory::CreateMesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, const Color& color)
{
	Mesh* mesh = new Mesh(vertexBuffer, indexBuffer, color);

	return mesh;
}

Mesh* MeshFactory::CreateCuboid(const Size3D& size, Texture2D* texture)
{
	float hw = size.width / 2;
	float hy = size.height / 2;
	float hz = size.depth / 2;

	float vertices[] = {
		// front
		-hw, -hy,  hz,
		hw, -hy,  hz,
		hw,  hy,  hz,
		-hw,  hy,  hz,
		// back
		-hw, -hy, -hz,
		hw, -hy, -hz,
		hw,  hy, -hz,
		-hw,  hy, -hz
	};

	VertexBuffer* vbo = new VertexBuffer(&vertices,sizeof(VertexData), 8);

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

	return mesh;
}

Mesh* MeshFactory::CreateCuboid(const Size3D& size, const Color& color)
{
	float hw = size.width / 2;
	float hy = size.height / 2;
	float hz = size.depth / 2;

	float vertices[] = {
		// front
		-hw, -hy,  hz,
		hw, -hy,  hz,
		hw,  hy,  hz,
		-hw,  hy,  hz,
		// back
		-hw, -hy, -hz,
		hw, -hy, -hz,
		hw,  hy, -hz,
		-hw,  hy, -hz
	};

	VertexBuffer* vbo = new VertexBuffer(&vertices, sizeof(VertexData), 8);

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

	Mesh* mesh = new Mesh(vbo, ibo, color);

	return mesh;
}

Mesh* MeshFactory::CreateCube(float size, Texture2D* texture)
{
	float h = size / 2;

	float vertices[] = {
		// front
		-h, -h,  h,
		h, -h,  h,
		h,  h,  h,
		-h,  h,  h,
		// back
		-h, -h, -h,
		h, -h, -h,
		h,  h, -h,
		-h,  h, -h
	};

	VertexBuffer* vbo = new VertexBuffer(&vertices, sizeof(VertexData), 8);

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

	return mesh;
}

Mesh* MeshFactory::CreateCube(float size, const Color& color)
{
	float h = size / 2;

	float vertices[] = {
		// front
		-h, -h,  h,
		h, -h,  h,
		h,  h,  h,
		-h,  h,  h,
		// back
		-h, -h, -h,
		h, -h, -h,
		h,  h, -h,
		-h,  h, -h
	};

	VertexBuffer* vbo = new VertexBuffer(&vertices, sizeof(VertexData), 8);

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

	Mesh* mesh = new Mesh(vbo, ibo, color);

	return mesh;
}


//float cube_vertices[] = {
//	// front
//	-1.0, -1.0,  1.0,
//	1.0, -1.0,  1.0,
//	1.0,  1.0,  1.0,
//	-1.0,  1.0,  1.0,
//	// back
//	-1.0, -1.0, -1.0,
//	1.0, -1.0, -1.0,
//	1.0,  1.0, -1.0,
//	-1.0,  1.0, -1.0,
//};