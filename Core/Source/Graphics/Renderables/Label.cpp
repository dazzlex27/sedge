/*
===========================================================================
Label.cpp

Implements the Label class
===========================================================================
*/

#include "Label.h"
#include <freetype-gl.h>
#include "System/DeleteMacros.h"
#include "Graphics/Fonts/Font.h"
#include "Graphics/Structures/VertexData.h"

using namespace s3dge;
using namespace ftgl;

Label::Label(const std::string& text, Font* font, const Point2D& position, const float zIndex, const Size2D& size, const Color& color)
	: _text(text), _font(font), Renderable2D(Point3D(position.x, position.y, zIndex), size, color)
{
}

void Label::SetText(const std::string & text)
{
	_text = text;
	CreateTextTexture();
}

void Label::CreateTextTexture()
{
	if (Vertices != nullptr)
	{
		SafeDeleteArray(Vertices);
		VertexCount = 0;
	}

	if (Elements != nullptr)
	{
		SafeDeleteArray(Elements);
		ElementCount = 0;
	}

	Vertices = new VertexData[_text.length() * 4];
	Elements = new uint[_text.length() * 6];

	VertexData* buffer = Vertices;

	auto x = Position.x;

	const float scaleX = 40.0f;
	const float scaleY = 40.0f;

	uint offset = 0;

	for (uint i = 0; i < _text.length(); i++)
	{
		texture_glyph_t* glyph = texture_font_get_glyph(_font->GetFontFace(), _text[i]);

		if (glyph != NULL)
		{
			if (i > 0)
			{
				float kerning = texture_glyph_get_kerning(glyph, _text[i - 1]);
				x += kerning / scaleX;
			}

			float x0 = x + glyph->offset_x / scaleX;
			float y0 = Position.y + glyph->offset_y / scaleY;
			float x1 = x0 + glyph->width / scaleX;
			float y1 = y0 - glyph->height / scaleY;

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			buffer->Position = Point3D(x0, y1, 0);
			buffer->UV = Point2D(u0, v1);
			buffer->TextureID = 0;
			buffer->Color = Col;
			buffer++;

			buffer->Position = Point3D(x0, y0, 0);
			buffer->UV = Point2D(u0, v0);
			buffer->TextureID = 0;
			buffer->Color = Col;
			buffer++;

			buffer->Position = Point3D(x1, y0, 0);
			buffer->UV = Point2D(u1, v0);
			buffer->TextureID = 0;
			buffer->Color = Col;
			buffer++;

			buffer->Position = Point3D(x1, y1, 0);
			buffer->UV = Point2D(u1, v1);
			buffer->TextureID = 0;
			buffer->Color = Col;
			buffer++;

			x += glyph->advance_x / scaleX;

			Elements[ElementCount + 0] = VertexCount + 0;
			Elements[ElementCount + 1] = VertexCount + 1;
			Elements[ElementCount + 2] = VertexCount + 2;

			Elements[ElementCount + 3] = VertexCount + 2;
			Elements[ElementCount + 4] = VertexCount + 3;
			Elements[ElementCount + 5] = VertexCount + 0;

			VertexCount += 4;
			ElementCount += 6;
		}
	}
}

const uint Label::GetTextureID() const
{
	return _font->GetAtlasID();
}
