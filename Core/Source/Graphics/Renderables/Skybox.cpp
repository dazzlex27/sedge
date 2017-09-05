/*
===========================================================================
Skybox.ñpp

implements the Skybox class.
===========================================================================
*/

#include "Skybox.h"
#include "Graphics/Textures/Cubemap.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/GraphicsAPI.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Structures/VertexData.h"

using namespace s3dge;

Skybox::Skybox(Cubemap*const texture)
	: _texture(texture)
{
	VertexDataCb vertices[24];

	// front face
	vertices[0].Position = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[0].UV = Vector3(1.0f, 1.0f, -1.0f);
	vertices[1].Position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[1].UV = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[2].Position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[2].UV = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[3].Position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[3].UV = Vector3(1.0f, -1.0f, -1.0f);

	// left face
	vertices[4].Position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[4].UV = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[5].Position = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[5].UV = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[6].Position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[6].UV = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[7].Position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[7].UV = Vector3(-1.0f, -1.0f, -1.0f);

	// right face
	vertices[8].Position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[8].UV = Vector3(1.0f, 1.0f, 1.0f);
	vertices[9].Position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[9].UV = Vector3(1.0f, 1.0f, -1.0f);
	vertices[10].Position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[10].UV = Vector3(1.0f, -1.0f, -1.0f);
	vertices[11].Position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[11].UV = Vector3(1.0f, -1.0f, 1.0f);

	// back face
	vertices[12].Position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[12].UV = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[13].Position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[13].UV = Vector3(1.0f, 1.0f, 1.0f);
	vertices[14].Position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[14].UV = Vector3(1.0f, -1.0f, 1.0f);
	vertices[15].Position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[15].UV = Vector3(-1.0f, -1.0f, 1.0f);

	// top face
	vertices[16].Position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[16].UV = Vector3(1.0f, 1.0f, 1.0f);
	vertices[17].Position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[17].UV = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[18].Position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[18].UV = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[19].Position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[19].UV = Vector3(1.0f, 1.0f, -1.0f);

	// bottom face
	vertices[20].Position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[20].UV = Vector3(1.0f, -1.0f, -1.0f);
	vertices[21].Position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[21].UV = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[22].Position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[22].UV = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[23].Position = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[23].UV = Vector3(1.0f, -1.0f, 1.0f);

	uint elements[36];
	int offset = 0;

	for (int i = 0; i < 36; i += 6)
	{
		elements[i + 0] = 0 + offset;
		elements[i + 1] = 1 + offset;
		elements[i + 2] = 2 + offset;
		elements[i + 3] = 2 + offset;
		elements[i + 4] = 3 + offset;
		elements[i + 5] = 0 + offset;
		offset += 4;
	}

	const uint vertexSize = sizeof(VertexDataCb);

	_vao = new VertexArray();
	_vbo = new VertexBuffer(vertexSize, sizeof(vertices) / vertexSize, &vertices);
	_ebo = new ElementBuffer(sizeof(elements) / sizeof(uint), (uint*)(&elements));

	_vao->Bind();
	_vbo->Bind();
	_ebo->Bind();

	_vao->SetLayout(VertexLayout::GetDefaultSkyboxVertexLayout());

	_vao->Unbind();
	_vbo->Unbind();
	_ebo->Unbind();
}

void Skybox::Draw() const
{
	_texture->Bind();

	_vao->Bind();
	_vao->DrawElements(_ebo->GetCount());
	_vao->Unbind();
}