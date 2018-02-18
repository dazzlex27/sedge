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
	class Renderer2D;

	class Label : public Renderable2D
	{
	private:
		std::string _text;
		Font* _font;

	public:
		Label(const char*const text, Font*const font, const Vector2& position, const float zIndex, const Size2D& size, const Color& color = Color(0xffffffff));

	public:
		void SetText(const std::string& text);
		const std::string& GetText() const { return _text; }

		virtual const ID GetTextureID() const override;

		void Submit(Renderer2D*const renderer2d) const override;

		friend class LabelFactory;
	};
}