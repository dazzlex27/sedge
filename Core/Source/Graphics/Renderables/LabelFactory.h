/*
===========================================================================
LabelFactory.h

Declares LabelFactory class that is responsible for creating Label instances.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Graphics/Structures/Color.h"

namespace s3dge
{
	struct Point2D;
	struct Size2D;

	namespace graphics
	{
		class Label;
		class Font;

		class LabelFactory
		{
		public:
			static Label* CreateLabel(cstring text, Font* font, const Point2D& position, const Size2D& size, const Color& color = Color(0xffffffff));
		};
	}
}
