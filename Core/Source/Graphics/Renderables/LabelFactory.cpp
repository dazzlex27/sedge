/*
===========================================================================
LabelFactory.cpp

Implements the LabelFactory class
===========================================================================
*/

#include <string>
#include "LabelFactory.h"
#include "Graphics/Renderables/Label.h"

using namespace s3dge;

Label*const LabelFactory::CreateLabel(const char* text, Font*const font, const Vector2& position, const float zIndex, const Size2D& size, const Color& color)
{
	return new Label(std::string(text), font, position, zIndex, size, color);
}