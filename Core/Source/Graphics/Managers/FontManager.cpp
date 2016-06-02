/*
===========================================================================
FontManager.cpp

Implements the FontManager class.
===========================================================================
*/

#include "FontManager.h"
#include "Graphics/Fonts/FontFactory.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
	
std::map<std::string, Font*> FontManager::_fonts;
bool FontManager::_initialized;

void FontManager::Initialize()
{
	//_fonts.push_back(FontFactory::CreateDefaultFont());
	_initialized = true;
}

void FontManager::Add(const char*const name, const char*const path, const float size, const bool overrideExisting)
{
	if (_initialized)
	{
		if (Get(name) != nullptr)
		{
			if (overrideExisting)
			{
				Font* font = FontFactory::CreateFont(name, path, size);
				if (font != nullptr)
					_fonts[name] = font;
			}
			else
			{
				LOG_WARNING("Font \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}
			
		Font* font = FontFactory::CreateFont(name, path, size);
		if (font != nullptr)
			_fonts[name] = font;
	}
	else
	{
		LOG_WARNING("Font manager was not initialized before adding a font (", name, ")");
	}
}

Font* FontManager::Get(const char*const name)
{
	if (_initialized)
	{
		if (_fonts.find(name) != _fonts.end())
			return _fonts[name];
	}
	else
	{
		LOG_WARNING("Font manager was not initialized before getting a font (", name, ")");
	}

	return nullptr;
}

void FontManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _fonts)
			SafeDelete(item.second);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the font manager as it was not initialized!");
	}
}