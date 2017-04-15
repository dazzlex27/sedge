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
using namespace graphics;

Label* LabelFactory::CreateLabel(cstring text, Font* font, const Point2D& position, const Size2D& size, const Color& color)
{
	return new Label(std::string(text), font, position, size, color);
}