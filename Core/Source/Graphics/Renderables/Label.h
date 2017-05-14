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

	class Label : public Renderable2D
	{
	public:
		std::string text;
		Font* font;

	private:
		Label(const std::string& text, Font* font, const Point2D& position, float zIndex, const Size2D& size, const Color& color = Color(0xffffffff));

	public:
		void Submit(Renderer2D* renderer) const override;

		friend class LabelFactory;
	};
}