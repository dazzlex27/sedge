/*
===========================================================================
FontManager.cpp

Implements the FontManager class.
===========================================================================
*/

#include "FontManager.h"
#include "Graphics/Fonts/FontFactory.h"
#include "System/Logger.h"
#include "System/MemoryManagement.h"

using namespace s3dge;
	
void FontManager::AddFont(const char*const name, const char*const path, const float size, const bool overrideExisting)
{
	if (GetFont(name) != nullptr)
	{
		if (overrideExisting)
		{
			Font*const font = FontFactory::CreateFont(name, path, size);
			if (font != nullptr)
				_fonts[name] = font;
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
			_fonts[name] = font;
	}
}

Font*const FontManager::GetFont(const char*const name)
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