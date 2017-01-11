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
			maths::vec2f position;
			uint color;

			Label(const std::string& text, Font* font, float x, float y, float width, float height, uint color);
			~Label();

			void Submit(Renderer2D* renderer) const override;
			inline const maths::vec3f GetPosition() const override { return maths::vec3f(position.x, position.y, 0); }
		};
	}
}