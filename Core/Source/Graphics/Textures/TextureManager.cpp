/*
===========================================================================
TextureManager.cpp

Implements the texture manager class.
===========================================================================
*/

#include "TextureManager.h"
#include "TextureFactory.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
	
std::vector<Texture2D*> TextureManager::_textures;
bool TextureManager::_initialized;

void TextureManager::Initialize()
{
	//_textures.push_back(TextureFactory::CreateDefaultTexture());
	_initialized = true;
}

void TextureManager::Add(const char* name, const char* path, TextureWrapMode wrapMode, TextureFilterMode filterMode, bool overrideExisting)
{
	if (_initialized)
	{
		if (Get(name) != nullptr)
		{
			if (overrideExisting)
			{
				Texture2D* newTexture = TextureFactory::CreateTextureFromFile(name, path, wrapMode, filterMode);
				if (newTexture != nullptr)
					_textures.push_back(newTexture);
			}
			else
			{
				LOG_WARNING("Texture \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Texture2D* newTexture = TextureFactory::CreateTextureFromFile(name, path, wrapMode, filterMode);
		if (newTexture != nullptr)
			_textures.push_back(newTexture);
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before adding a texture file (", name, ")");
	}
}

Texture2D* TextureManager::Get(const char* name)
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