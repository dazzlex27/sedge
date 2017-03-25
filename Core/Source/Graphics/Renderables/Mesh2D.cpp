#include "Mesh2D.h"

#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/Buffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace graphics;
using namespace std;

Mesh2D::Mesh2D(Buffer* vbo, IndexBuffer* ibo, const Color& color)
	: _ibo(ibo), _color(color)
{
	_vao = new VertexArray();
	_vao->AddBuffer(vbo);
}

Mesh2D::~Mesh2D()
{
	SafeDelete(_vao);
	SafeDelete(_ibo);
}

void Mesh2D::Render()
{
}
