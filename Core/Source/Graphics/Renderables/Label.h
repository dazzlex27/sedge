/*
===========================================================================
Label.h

Represents a class designed to store text glyphs.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Renderable2D.h"

namespace s3dge
{
	namespace graphics
	{
		class Font;

		class Label : public Renderable2D
		{
		public:
			std::string text;
			Font* font;

			Label(const std::string& text, Font* font, float x, float y, float width, float height, const Color& color);
			~Label();

			void Submit(Renderer2D* renderer) const override;
		};
	}
}