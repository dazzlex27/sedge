/*
===========================================================================
FontFactory.cpp

Implements FontFactory class
===========================================================================
*/

#include "FontFactory.h"
#include "System/FileUtils.h"
#include "System/Logger.h"

using namespace sedge;

Font* FontFactory::CreateFont(const char*const name, const char*const path, const float size)
{
	if (strcmp(name, "") == 0)
	{
		LOG_ERROR("Cannot create a font with an empty name string");
		return nullptr;
	}

	if (strcmp(path, "") == 0)
	{
		LOG_ERROR("Cannot create a font with an empty path string");
		return nullptr;
	}

	if (!FileUtils::CheckFileExists(path))
	{
		LOG_ERROR("Font file \"", name, "\" was not found");
		return nullptr;
	}

	if (size < 0.1)
	{
		LOG_ERROR("Font size was less than 0.1, \"", name, "\" will not be created");
		return nullptr;
	}

	Font* font = new Font(name, path, size);

	if (!font->LoadFontFromFile())
	{
		LOG_ERROR("Failed to load font \"", name, "\"");
		return nullptr;
	}

	return font;
}