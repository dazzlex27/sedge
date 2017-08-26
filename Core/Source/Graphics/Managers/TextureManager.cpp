/*
===========================================================================
TextureManager.cpp

Implements the texture manager class.
===========================================================================
*/

#include "TextureManager.h"
#include "Graphics/Textures/TextureFactory.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
using namespace std;
	
map<string, Texture2D*> TextureManager::_textures;
map<id, string> TextureManager::_idsToNames;
bool TextureManager::_initialized;

void TextureManager::Initialize()
{
	_initialized = true;
}

void TextureManager::Add(const char* name, const char* path, TextureType type, TextureWrapMode wrapMode, TextureFilterMode filterMode, bool overrideExisting)
{
	if (_initialized)
	{
		if (Get(name) != nullptr)
		{
			if (overrideExisting)
			{
				Texture2D* newTexture = TextureFactory::CreateTextureFromFile(name, path, type, wrapMode, filterMode);
				if (newTexture != nullptr)
				{
					_textures[name] = newTexture;
					_idsToNames[newTexture->GetID()] = name;
				}
			}
			else
			{
				LOG_WARNING("Texture \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Texture2D* newTexture = TextureFactory::CreateTextureFromFile(name, path, type, wrapMode, filterMode);
		if (newTexture != nullptr)
		{
			_textures[name] = newTexture;
			_idsToNames[newTexture->GetID()] = name;
		}
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before adding a texture file (", name, ")");
	}
}

Texture2D*const TextureManager::Get(const char* name)
{
	if (_initialized)
	{
		if (_textures.find(name) != _textures.end())
			return _textures[name];

		return nullptr;
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before getting a texture (", name, ")");
	}

	return nullptr;
}

Texture2D*const TextureManager::GetByID(const id ID)
{
	if (_idsToNames.find(ID) != _idsToNames.end())
		return _textures[_idsToNames[ID]];

	return nullptr;
}

void TextureManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _textures)
			SafeDelete(item.second);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the texture manager as it was not initialized!");
	}
}