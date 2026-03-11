/*
===========================================================================
FontManager.cpp

Implements the FontManager class.
===========================================================================
*/

#include "FontManager.h"
#include <Graphics/Fonts/FontFactory.h>
#include <System/Logger.h>
#include <System/MemoryManagement.h>

using namespace sedge;
	
void FontManager::AddFont(const char*const name, const char*const path, const float size, const bool overrideExisting)
{
	std::string key(name);
	if (GetFont(key) != nullptr)
	{
		if (overrideExisting)
		{
			Font*const font = FontFactory::CreateFont(name, path, size);
			if (font != nullptr)
				_fonts[key] = font;
		}
		else
		{
			LOG_WARNING("Font \"", name, "\" already exists and will not be overwritten");
		}
	}
	else
	{
		Font*const font = FontFactory::CreateFont(name, path, size);
		if (font != nullptr)
			_fonts[key] = font;
	}
}

Font*const FontManager::GetFont(const std::string& name)
{
	if (_fonts.find(name) != _fonts.end())
		return _fonts[name];

	return nullptr;
}

FontManager::~FontManager()
{
	for (auto item : _fonts)
		SafeDelete(item.second);
}