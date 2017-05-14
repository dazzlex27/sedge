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
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Renderers/Renderer.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Structures/VertexData.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
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

Mesh::Mesh(VertexBuffer* vbo, ElementBuffer* ibo)
	: _ibo(ibo), _vbo(vbo), texture(nullptr)
{
	_vao = new VertexArray();

	_vao->Bind();
	vbo->SetLayout(&GetDefaultLayout());
	_vao->Unbind();

	_vao->AddBuffer(vbo);
}

Mesh::Mesh(VertexBuffer* vbo, ElementBuffer* ibo, Texture2D* texture)
	: _ibo(ibo), texture(texture), _vbo(vbo)
{
	_vao = new VertexArray();

	_vao->Bind();
	vbo->SetLayout(&GetDefaultLayout());
	_vao->AddBuffer(vbo);

	_vao->Unbind();
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
	_vbo->Bind();
	_vao->Bind();
	_ibo->Bind();
	_vao->Draw(_ibo->GetCount());
	_ibo->Unbind();
	_vao->Unbind();
	_vbo->Unbind();
}
