/*
===========================================================================
TextureManager.cpp

Implements the texture manager class.
===========================================================================
*/

#include "TextureManager.h"
#include "TextureFactory.h"
#include "Internal/Log.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace graphics;
	
std::vector<Texture*> TextureManager::_textures;
bool TextureManager::_initialized;

void TextureManager::Initialize()
{
	//_textures.push_back(TextureFactory::CreateDefaultTexture());
	_initialized = true;
}

void TextureManager::Add(cstring name, cstring path, bool overrideExisting)
{
	if (_initialized)
	{
		if (Get(name) != nullptr)
		{
			if (overrideExisting)
			{
				Texture* newTexture = TextureFactory::CreateTexture(name, path);
				if (newTexture != nullptr)
					_textures.push_back(newTexture);
			}
			else
			{
				LOG_WARNING("Texture \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Texture* newTexture = TextureFactory::CreateTexture(name, path);
		if (newTexture != nullptr)
			_textures.push_back(newTexture);
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before adding a texture file (", name, ")");
	}
}

Texture* TextureManager::Get(cstring name)
{
	if (_initialized)
	{
		for (auto item : _textures)
			if (strcmp(item->GetName(), name) == 0)
				return item;
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before getting a texture (", name, ")");
	}

	return nullptr;
}

void TextureManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _textures)
			SafeDelete(item);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the texture manager as it was not initialized!");
	}
}