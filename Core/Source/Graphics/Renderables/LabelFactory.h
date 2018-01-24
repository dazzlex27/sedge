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
	struct Vector2;
	struct Size2D;

	class Label;
	class Font;

	class LabelFactory
	{
	public:
		Label*const CreateLabel(const char* text, Font*const font, const Vector2& position, float zIndex, const Size2D& size, const Color& color = Color(0xffffffff));
	};
}
