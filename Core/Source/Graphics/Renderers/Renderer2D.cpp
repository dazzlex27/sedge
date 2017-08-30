/*
===========================================================================
Renderer2D.cpp

Implements the Renderer2D class
===========================================================================
*/

#include "Renderer2D.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Structures/VertexData.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Fonts/Font.h"
#include "Graphics/Renderables/Renderable2D.h"

#include "System/DeleteMacros.h"
#include "System/Log.h"

#include "freetype-gl.h"

using namespace s3dge;
using namespace ftgl;

static uint* FillElementBuffer(const uint maxElement);

Renderer2D::Renderer2D(const uint maxVertices)
	: _maxVertices(maxVertices)
{
	if (_maxVertices == 0)
	{
		LOG_ERROR("Sprite renderer: max vertices == 0");
		abort();
	}

	_vao = new VertexArray();
	_vao->Bind();

	_vbo = new VertexBuffer(sizeof(VertexDataS), _maxVertices);
	_vbo->Bind();

	const uint maxElements = (const uint)(_maxVertices * 1.5);
	uint* elements = FillElementBuffer(maxElements);
	_ebo = new ElementBuffer(maxElements, elements);
	SafeDeleteArray(elements);
	_ebo->Bind();

	_vao->SetLayout(VertexLayout::GetDefaultVertexLayoutSprite());

	_vao->Unbind();
	_vbo->Unbind();
	_ebo->Unbind();

	_elementCount = 0;
}

Renderer2D::~Renderer2D()
{
	SafeDelete(_vao);
	SafeDelete(_vbo);
	SafeDelete(_ebo);
}

void Renderer2D::Begin()
{
	_vbo->Bind();
	_vbo->Map();
	_buffer = (VertexDataS*)_vbo->GetDataPointer();
}

void Renderer2D::Submit(const Renderable2D*const sprite)
{
	const Vector3& position = sprite->GetPosition();
	const Size2D& size = sprite->GetSize();
	const Color& color = sprite->GetColor();
	const float samplerIndex = GetSamplerIndexByTID(sprite->GetTextureID());

	_buffer->Position = Vector3(position.x, position.y - size.height, position.z);
	_buffer->Color = color;
	_buffer->UV = Vector2(0, 0);
	_buffer->TextureID = samplerIndex;
	_buffer++;

	_buffer->Position = Vector3(position.x, position.y, position.z);
	_buffer->Color = color;
	_buffer->UV = Vector2(0, 1);
	_buffer->TextureID = samplerIndex;
	_buffer++;

	_buffer->Position = Vector3(position.x + size.width, position.y, position.z);
	_buffer->Color = color;
	_buffer->UV = Vector2(1, 1);
	_buffer->TextureID = samplerIndex;
	_buffer++;

	_buffer->Position = Vector3(position.x + size.width, position.y - size.height, position.z);
	_buffer->Color = color;
	_buffer->UV = Vector2(1, 0);
	_buffer->TextureID = samplerIndex;
	_buffer++;

	_elementCount += 6;
}

void Renderer2D::RenderText(const char* text, const Font*const font, const Vector3& position, const Color& color)
{
	const float samplerIndex = GetSamplerIndexByTID(font->GetAtlasID());

	const float scaleX = font->GetScaleX();
	const float scaleY = font->GetScaleY();
	
	float x = position.x;

	for (uint i = 0; i < strlen(text); i++)
	{
		texture_glyph_t*const glyph = texture_font_get_glyph(font->GetFontFace(), text[i]);

		if (glyph)
		{
			if (i > 0)
			{
				const float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
				x += kerning / scaleX;
			}

			const float x0 = x + glyph->offset_x / scaleX;
			const float y0 = position.y + glyph->offset_y / scaleY;
			const float x1 = x0 + glyph->width / scaleX;
			const float y1 = y0 - glyph->height / scaleY;

			const float u0 = glyph->s0;
			const float v0 = glyph->t0;
			const float u1 = glyph->s1;
			const float v1 = glyph->t1;

			x += glyph->advance_x / scaleX;

			_buffer->Position = Vector3(x0, y1, 0);
			_buffer->UV = Vector2(u0, v1);
			_buffer->TextureID = samplerIndex;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Vector3(x0, y0, 0);
			_buffer->UV = Vector2(u0, v0);
			_buffer->TextureID = samplerIndex;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Vector3(x1, y0, 0);
			_buffer->UV = Vector2(u1, v0);
			_buffer->TextureID = samplerIndex;
			_buffer->Color = color;
			_buffer++;

			_buffer->Position = Vector3(x1, y1, 0);
			_buffer->UV = Vector2(u1, v1);
			_buffer->TextureID = samplerIndex;
			_buffer->Color = color;
			_buffer++;

			_elementCount += 6;
		}
	}
}

void Renderer2D::End()
{
	_vbo->Unmap();
	_vbo->Unbind();
}

void Renderer2D::Flush()
{
	for (uint i = 0; i < _textureIDs.size(); i++)
	{
		Texture2D::ActivateTexture(i);
		Texture2D::BindById(TextureTarget::Tex2D, _textureIDs[i]);
	}

	_vao->Bind();
	_vao->DrawElements(_elementCount);
	_vao->Unbind();

	_elementCount = 0;
}

const float Renderer2D::GetSamplerIndexByTID(const id texID)
{
	if (texID == 0)
		return -1.0f;

	for (uint i = 0; i < _textureIDs.size(); ++i)
	{
		if (_textureIDs[i] == texID)
			return (const float)i;
	}

	if (_textureIDs.size() >= 32)
	{
		End();
		Flush();
		Begin();
	}

	_textureIDs.push_back(texID);

	return (const float)_textureIDs.size();
}

static uint* FillElementBuffer(const uint maxElements)
{
	uint* elements = new uint[maxElements];

	for (uint i = 0, offset = 0; i < maxElements; i += 6, offset += 4)
	{
		elements[i] = offset + 0;
		elements[i + 1] = offset + 1;
		elements[i + 2] = offset + 2;

		elements[i + 3] = offset + 2;
		elements[i + 4] = offset + 3;
		elements[i + 5] = offset + 0;
	}

	return elements;
}