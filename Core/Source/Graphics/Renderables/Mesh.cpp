/*
===========================================================================
Mesh.cpp

Implemlents the Mesh class
===========================================================================
*/

#include "Mesh.h"

#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Internal/DeleteMacros.h"
#include "Graphics/Renderers/Renderer.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Structures/VertexData.h"

using namespace s3dge;
using namespace graphics;
using namespace std;

#define GL_FLOAT 0x1406
#define GL_UNSIGNED_BYTE 0x1401

VertexLayout GetDefaultLayout()
{
	VertexLayout layout;
	layout.AddEntry("position", 0, 3, GL_FLOAT, 0, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Position)));
	layout.AddEntry("color", 1, 4, GL_UNSIGNED_BYTE, 1, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Color)));
	layout.AddEntry("uv", 2, 2, GL_FLOAT, 0, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::UV)));
	layout.AddEntry("textureID", 3, 1, GL_FLOAT, 0, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::TextureID)));

	return layout;
}

Mesh::Mesh(VertexBuffer* vbo, IndexBuffer* ibo, const Color& color)
	: _ibo(ibo), color(color), _vbo(vbo), texture(nullptr)
{
	_vao = new VertexArray();

	_vao->Bind();
	vbo->SetLayout(&GetDefaultLayout());
	_vao->Unbind();

	_vao->AddBuffer(vbo);
}

Mesh::Mesh(VertexBuffer* vbo, IndexBuffer* ibo, Texture2D* texture)
	: _ibo(ibo), texture(texture), _vbo(vbo), color(0xffffffff)
{
	_vao = new VertexArray();

	_vao->Bind();
	vbo->SetLayout(&GetDefaultLayout());
	_vao->Unbind();

	_vao->AddBuffer(vbo);
}

Mesh::~Mesh()
{
	SafeDelete(_vao);
	SafeDelete(_ibo);
}

void Mesh::Submit(Renderer* renderer) const
{
	renderer->SubmitMesh(this);
}

void Mesh::Render() const
{
	_vao->Bind();
	_vbo->Bind();
	_ibo->Bind();
	_vao->Draw(_ibo->GetCount());
	_ibo->Unbind();
	_vbo->Unbind();
	_vao->Unbind();
}