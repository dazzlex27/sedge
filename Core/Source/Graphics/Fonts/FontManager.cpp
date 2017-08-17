/*
===========================================================================
FontManager.cpp

Implements the font manager class.
===========================================================================
*/

#include "FontManager.h"
#include "FontFactory.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
	
std::vector<Font*> FontManager::_fonts;
bool FontManager::_initialized;

void FontManager::Initialize()
{
	//_fonts.push_back(FontFactory::CreateDefaultFont());
	_initialized = true;
}

void FontManager::Add(const char* name, const char* path, float size, bool overrideExisting)
{
	if (_initialized)
	{
		if (Get(name) != nullptr)
		{
			if (overrideExisting)
			{
				Font* newFont = FontFactory::CreateFont(name, path, size);
				if (newFont != nullptr)
					_fonts.push_back(newFont);
			}
			else
			{
				LOG_WARNING("Font \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}
			
		Font* newFont = FontFactory::CreateFont(name, path, size);
		if (newFont != nullptr)
			_fonts.push_back(newFont);
	}
	else
	{
		LOG_WARNING("Font manager was not initialized before adding a font file (", name, ")");
	}
}

Font* FontManager::Get(const char* name)
{
	if (_initialized)
	{
		for (auto item : _fonts)
			if (strcmp(item->GetName(), name) == 0)
				return item;
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
			SafeDelete(item);

		_initialized = true;
	}
	else
	{
		LOG_WARNING("Cannot dispose the font manager as it was not initialized!");
	}
}