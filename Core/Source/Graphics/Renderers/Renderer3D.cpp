/*
===========================================================================
Renderer3D.cpp

Implements the Renderer3D class
Set up to process up to 2,000,000 vertices per frame.
===========================================================================
*/

#include "Renderer3D.h"
#include <GL/glew.h>
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Renderables/Renderable.h"
#include "Graphics/Structures/Color.h"
#include "Graphics/Structures/VertexLayout.h"
#include "System/DeleteMacros.h"
#include "System/Log.h"

using namespace s3dge;

#define MAX_VERTICES 2000000 
#define MAX_ELEMENTS 4000000

Renderer3D::Renderer3D()
{
	Initialize();
}

Renderer3D::~Renderer3D()
{
	SafeDelete(_vao);
	SafeDelete(_vbo);
	SafeDelete(_ebo);
}

void Renderer3D::Initialize()
{
	_elementCount = 0;

	_vao = new VertexArray();

	_vao->Bind();
	_vbo = new VertexBuffer(sizeof(VertexData), MAX_VERTICES);

	VertexLayout layout;
	layout.AddEntry("position", 0, 3, ElementType::FLOAT, GL_FALSE, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Position)));
	layout.AddEntry("color", 1, 4, ElementType::UBYTE, GL_TRUE, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Color)));
	layout.AddEntry("uv", 2, 2, ElementType::FLOAT, GL_FALSE, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::UV)));
	layout.AddEntry("textureID", 3, 1, ElementType::FLOAT, GL_FALSE, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::TextureID)));

	_vbo->SetLayout(&layout);
	_vao->AddBuffer(_vbo);

	uint* elements = new uint[MAX_ELEMENTS];
	_ebo = new ElementBuffer(MAX_ELEMENTS, elements);
}

void Renderer3D::Begin()
{
	_vbo->Bind();
	_vbo->Map();
	_vertexBuffer = (VertexData*)_vbo->GetDataPointer();
	_ebo->Bind();
	_ebo->Map();
	_elementBuffer = (uint*)_ebo->GetDataPointer();
}

void Renderer3D::Submit(const Renderable* renderable)
{
	const VertexData* vertices = renderable->GetVertexData();
	const uint* elements = renderable->GetElementData();

	for (uint i = 0; i < renderable->GetVertexCount(); i++)
	{
		*_vertexBuffer = vertices[i];
		_vertexBuffer++;
	}

	for (uint i = 0; i < renderable->GetElementCount(); i++)
	{
		*_elementBuffer = elements[i] + _elementCount;
		_elementBuffer++;
	}

	_elementCount += renderable->GetElementCount();
}

void Renderer3D::End()
{
	_vbo->Unmap();
	_vbo->Unbind();
	_ebo->Unmap();
	_ebo->Unbind();
}

void Renderer3D::Flush()
{
	for (uint i = 0; i < _textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
	}

	_vao->Bind();
	_ebo->Bind();

	_vao->Draw(_elementCount);

	_ebo->Unbind();
	_vao->Unbind();

	_elementCount = 0;
}