/*
===========================================================================
Label.h

Represents a class designed to store text glyphs.
===========================================================================
*/

#pragma once

#include <string>
#include "CustomTypes.h"
#include "Renderable2D.h"

namespace s3dge
{
	class Font;
	struct VertexData;

	class Label : public Renderable2D
	{
	private:
		std::string _text;
		Font* _font;

	private:
		Label(const std::string& text, Font* font, const Point2D& position, const float zIndex, const Size2D& size, const Color& color = Color(0xffffffff));

	public:
		void SetText(const std::string& text);
		const std::string& GetText() const { return _text; }

		virtual const uint GetTextureID() const override;

		friend class LabelFactory;

	private:
		void CreateTextTexture();
	};
}