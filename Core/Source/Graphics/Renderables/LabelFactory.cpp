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

Label* LabelFactory::CreateLabel(cstring text, Font* font, const Point2D& position, float zIndex, const Size2D& size, const Color& color)
{
	return new Label(std::string(text), font, position, zIndex, size, color);
}