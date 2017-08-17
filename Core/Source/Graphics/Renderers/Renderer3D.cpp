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
#include "Graphics/Textures/Texture2D.h"

using namespace s3dge;

#define MAX_VERTICES 200000 
#define MAX_ELEMENTS 400000

Renderer3D::Renderer3D()
{
	_elementCount = 0;
	_elementOffset = 0;

	_vao = new VertexArray();
	_vbo = new VertexBuffer(sizeof(VertexData), MAX_VERTICES);
	uint* elements = new uint[MAX_ELEMENTS];
	_ebo = new ElementBuffer(MAX_ELEMENTS, elements);

	_vao->Bind();
	_vbo->Bind();
	_ebo->Bind();

	_vao->SetLayout(VertexLayout::GetDefaultVertexLayout());

	_vao->Unbind();
	_vbo->Unbind();
	_ebo->Unbind();

	_textureMaxCount = 32;
}

Renderer3D::~Renderer3D()
{
	SafeDelete(_vao);
	SafeDelete(_vbo);
	SafeDelete(_ebo);
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
	const uint vertexCount = renderable->GetVertexCount();
	const uint* elements = renderable->GetElementData();
	const uint elementCount = renderable->GetElementCount();
	const uint textureID = renderable->GetTextureID();

	const float textureIndex = GetTextureIndexByID(textureID);

	for (uint i = 0; i < vertexCount; i++)
	{
		*_vertexBuffer = vertices[i];
		_vertexBuffer->TextureID = textureIndex;
		_vertexBuffer++;
	}

	for (uint i = 0; i < elementCount; i++)
	{
		*_elementBuffer = elements[i] + _elementOffset;
		_elementBuffer++;
	}

	_elementOffset += vertexCount;
	_elementCount += elementCount;
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
	_vao->Draw(_elementCount);
	_vao->Unbind();

	_elementOffset = 0;
	_elementCount = 0;
}

const float Renderer3D::GetTextureIndexByID(const id textureID)
{
	if (textureID == 0)
		return -1.0f;

	for (id i = 0; i < _textures.size(); ++i)
	{
		if (_textures[i] == textureID)
			return i;
	}

	if (_textures.size() >= _textureMaxCount)
	{
		End();
		Flush();
		Begin();
	}

	_textures.push_back(textureID);

	return (const float)(_textures.size());
}