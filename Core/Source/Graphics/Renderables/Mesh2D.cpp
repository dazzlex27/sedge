#include "Mesh2D.h"

#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace graphics;
using namespace std;

Mesh2D::Mesh2D(VertexBuffer* vbo, IndexBuffer* ibo, const Color& color)
	: _ibo(ibo), _color(color), _vbo(vbo)
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
	_vao->Bind();
	_vbo->Bind();
	_ibo->Bind();
	_vao->Draw(_ibo->GetCount());
	_ibo->Unbind();
	_vbo->Unbind();
	_vao->Unbind();
}
