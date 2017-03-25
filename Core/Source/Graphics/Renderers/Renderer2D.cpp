/*
===========================================================================
Renderer2D.cpp

Implements the Renderer2D class
Set up to process up to 250,000 vertices per frame.
===========================================================================
*/

#include "Renderer2D.h"
#include "Internal/DeleteMacros.h"
#include "Internal/Log.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/Buffer.h"
#include "Graphics/Renderables/Renderable2D.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Fonts/Font.h"
#include "Graphics/Structures/Color.h"
#include "Graphics/Renderables/Mesh2D.h"

using namespace s3dge;
using namespace graphics;
using namespace ftgl;

#define MAX_VERTICES 250000
#define VERTEX_SIZE sizeof(VertexData)
#define VERTEX_BUFFER_SIZE VERTEX_SIZE * MAX_VERTICES
#define INDEX_BUFFER_SIZE VERTEX_BUFFER_SIZE
	
Renderer2D::Renderer2D()
{			
	Initialize();
}

Renderer2D::~Renderer2D()
{
	SafeDelete(_ibo);
	SafeDelete(_vao);
	SafeDelete(_vbo);
}

void Renderer2D::Initialize()
{
	_vao = new VertexArray();

	_vbo = new Buffer(_buffer, sizeof(VertexData), MAX_VERTICES);

	_vao->AddBuffer(_vbo);

	_vao->Bind();
		
	uint* indices = new uint[INDEX_BUFFER_SIZE];

	int offset = 0;

	for (int i = 0; i < INDEX_BUFFER_SIZE; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	_ibo = new IndexBuffer(indices, INDEX_BUFFER_SIZE);

	_indexCount = 0;

	_vao->Unbind();
}

void Renderer2D::Begin()
{
	_vbo->Bind();
	_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Renderer2D::Submit(const Renderable2D* renderable)
{
	auto position = renderable->GetPosition();
	auto size = renderable->GetSize();
	auto color = renderable->GetColor();
	auto uv = renderable->GetUV();
	auto textureID = renderable->GetTextureID();

	auto textureSlot = 0.0f;

	if (textureID > 0)
		textureSlot = GetTextureSlotByID(textureID);

	_buffer->Position = Point3D(position.x, position.y, position.z);
	_buffer->Color = color;
	_buffer->UV = uv[0];
	_buffer->TextureID = textureSlot;
	_buffer++;

	_buffer->Position = Point3D(position.x, position.y + size.height, position.z);
	_buffer->Color = color;
	_buffer->UV = uv[1];
	_buffer->TextureID = textureSlot;
	_buffer++;

	_buffer->Position = Point3D(position.x + size.width, position.y + size.height, position.z);
	_buffer->Color = color;
	_buffer->UV = uv[2];
	_buffer->TextureID = textureSlot;
	_buffer++;

	_buffer->Position = Point3D(position.x + size.width, position.y, position.z);
	_buffer->Color = color;
	_buffer->UV = uv[3];
	_buffer->TextureID = textureSlot;
	_buffer++;

	_indexCount += 6;
}

void Renderer2D::DrawString(const std::string& text, Font* font, const Point3D& position, const Color& color)
{
	auto x = position.x;
	auto textureSlot = 0.0f;
	auto ok = false;

	textureSlot = GetTextureSlotByID(font->GetAtlasID());

	const float scaleX = 40.0f;
	const float scaleY = 40.0f;

	for (uint i = 0; i < text.length(); i++)
	{
		texture_glyph_t* glyph = texture_font_get_glyph(font->GetFontFace(), text[i]);
		if (glyph != NULL)
		{
			if (i > 0)
			{
				float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
				x += kerning / scaleX;
			}

			float x0 = x + glyph->offset_x / scaleX;
			float y0 = position.y + glyph->offset_y / scaleY;
			float x1 = x0 + glyph->width / scaleX;
			float y1 = y0 - glyph->height / scaleY;

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			_buffer->Position = Point3D(x0, y0, 0);
			_buffer->UV = Point2D(u0, v0);
			_buffer->TextureID = textureSlot;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Point3D(x0, y1, 0);
			_buffer->UV = Point2D(u0, v1);
			_buffer->TextureID = textureSlot;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Point3D(x1, y1, 0);
			_buffer->UV = Point2D(u1, v1);
			_buffer->TextureID = textureSlot;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Point3D(x1, y0, 0);
			_buffer->UV = Point2D(u1, v0);
			_buffer->TextureID = textureSlot;
			_buffer->Color = color;
			_buffer++;

			_indexCount += 6;

			x += glyph->advance_x / scaleX;
		}
	}
}

void Renderer2D::SubmitMesh(Mesh2D* mesh)
{
	_meshes.push_back(mesh);
}

void Renderer2D::Flush()
{
	for (uint i = 0; i < _textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
	}

	_vao->Bind();
	_ibo->Bind();

	_vao->Draw(_indexCount);

	_ibo->Unbind();
	_vao->Unbind();

	_indexCount = 0;

	//for (uint i = 0; i < _meshes.size(); i++)
	//	_meshes[i]->Render();
}

void Renderer2D::End()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	_vbo->Unbind();
}

float Renderer2D::GetTextureSlotByID(id textureID)
{
	if (textureID == 0)
	{
		LOG_ERROR("textureID was 0");
		return -1.0f;
	}

	float textureSlot = 0.0f;

	auto ok = false;
	for (uint i = 0; i < _textures.size(); ++i)
	{
		if (_textures[i] == textureID)
		{
			textureSlot = (float)(i + 1);
			ok = true;
			break;
		}
	}

	if (!ok)
	{
		if (_textures.size() >= 32)
		{
			End();
			Flush();
			Begin();
		}

		_textures.push_back(textureID);
		textureSlot = (float)(_textures.size());
	}

	return textureSlot;
}