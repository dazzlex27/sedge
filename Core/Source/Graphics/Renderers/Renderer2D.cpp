/*
===========================================================================
Renderer2D.cpp

Implements the Renderer2D class
Set up to process up to 200,000 vertices per frame.
===========================================================================
*/

#include "Renderer2D.h"
#include <GL/glew.h>
#include <freetype-gl.h>
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Renderables/Renderable2D.h"
#include "Graphics/Fonts/Font.h"
#include "Graphics/Structures/Color.h"
#include "Graphics/Renderables/Mesh.h"
#include "Graphics/Structures/VertexLayout.h"
#include "System/DeleteMacros.h"
#include "System/Log.h"

using namespace s3dge;
using namespace ftgl;

#define MAX_SPRITES 50000
#define MAX_VERTICES MAX_SPRITES * 4
#define MAX_ELEMENTS MAX_SPRITES * 6
	
Renderer2D::Renderer2D()
{			
	Initialize();
}

Renderer2D::~Renderer2D()
{
	SafeDelete(_ebo);
	SafeDelete(_vao);
}

void Renderer2D::Initialize()
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
	_vao->Unbind();

	_vao->AddBuffer(_vbo);
		
	uint* elements = new uint[MAX_ELEMENTS];

	int offset = 0;

	for (int i = 0; i < MAX_ELEMENTS; i += 6)
	{
		elements[i] = offset + 0;
		elements[i + 1] = offset + 1;
		elements[i + 2] = offset + 2;

		elements[i + 3] = offset + 2;
		elements[i + 4] = offset + 3;
		elements[i + 5] = offset + 0;

		offset += 4;
	}

	_ebo = new ElementBuffer(MAX_ELEMENTS, elements);
}

void Renderer2D::Begin()
{
	_vbo->Bind();
	_vbo->Map();
	_buffer = (VertexData*)_vbo->GetDataPointer();
}

void Renderer2D::Submit(const Renderable* renderable)
{
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

	_buffer->Position = Point3D(position.x, position.y - size.height, position.z);
	_buffer->Color = color;
	_buffer->UV = uv[0];
	_buffer->TextureID = textureSlot;
	_buffer++;

	_buffer->Position = Point3D(position.x, position.y, position.z);
	_buffer->Color = color;
	_buffer->UV = uv[1];
	_buffer->TextureID = textureSlot;
	_buffer++;
	
	_buffer->Position = Point3D(position.x + size.width, position.y, position.z);
	_buffer->Color = color;
	_buffer->UV = uv[2];
	_buffer->TextureID = textureSlot;
	_buffer++;

	_buffer->Position = Point3D(position.x + size.width, position.y - size.height, position.z);
	_buffer->Color = color;
	_buffer->UV = uv[3];
	_buffer->TextureID = textureSlot;
	_buffer++;

	_elementCount += 6;
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

			_buffer->Position = Point3D(x0, y1, 0);
			_buffer->UV = Point2D(u0, v1);
			_buffer->TextureID = textureSlot;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Point3D(x0, y0, 0);
			_buffer->UV = Point2D(u0, v0);
			_buffer->TextureID = textureSlot;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Point3D(x1, y0, 0);
			_buffer->UV = Point2D(u1, v0);
			_buffer->TextureID = textureSlot;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Point3D(x1, y1, 0);
			_buffer->UV = Point2D(u1, v1);
			_buffer->TextureID = textureSlot;
			_buffer->Color = color;
			_buffer++;

			_elementCount += 6;

			x += glyph->advance_x / scaleX;
		}
	}
}

void Renderer2D::SubmitMesh(const Mesh* mesh)
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
	_ebo->Bind();

	_vao->Draw(_elementCount);

	_ebo->Unbind();
	_vao->Unbind();

	_elementCount = 0;

	/*for (uint i = 0; i < _meshes.size(); i++)
		_meshes[i]->Render();*/
}

void Renderer2D::End()
{
	_vbo->Unmap();
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