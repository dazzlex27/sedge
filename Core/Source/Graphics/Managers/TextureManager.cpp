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
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/Cubemap.h"

using namespace s3dge;
using namespace std;
	
map<string, Texture2D*> TextureManager::_texture2Ds;
map<string, Cubemap*> TextureManager::_cubemaps;
map<ID, string> TextureManager::_idsToNames;
bool TextureManager::_initialized;

void TextureManager::Initialize()
{
	_initialized = true;
}

void TextureManager::AddTex2D(const char*const name, const char*const path, const TextureType type, const TextureWrapMode wrapMode, const TextureFilterMode filterMode, const bool overrideExisting)
{
	if (_initialized)
	{
		if (GetTex2D(name) != nullptr)
		{
			if (overrideExisting)
			{
				Texture2D* newTexture = TextureFactory::CreateTexture2DFromFile(name, path, type, wrapMode, filterMode);
				if (newTexture != nullptr)
				{
					_texture2Ds[name] = newTexture;
					_idsToNames[newTexture->GetID()] = name;
				}
			}
			else
			{
				LOG_WARNING("Texture \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Texture2D* newTexture = TextureFactory::CreateTexture2DFromFile(name, path, type, wrapMode, filterMode);
		if (newTexture != nullptr)
		{
			_texture2Ds[name] = newTexture;
			_idsToNames[newTexture->GetID()] = name;
		}
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before adding a texture file (", name, ")");
	}
}

void TextureManager::AddCubemap(const char*const name, const std::vector<std::string>& paths, const TextureWrapMode wrapMode, const TextureFilterMode filterMode, const bool overrideExisting)
{
	if (_initialized)
	{
		if (GetCubemap(name) != nullptr)
		{
			if (overrideExisting)
			{
				Cubemap* newTexture = TextureFactory::CreateCubemapFromFile(name, paths, wrapMode, filterMode);
				if (newTexture != nullptr)
				{
					_cubemaps[name] = newTexture;
					_idsToNames[newTexture->GetID()] = name;
				}
			}
			else
			{
				LOG_WARNING("Texture \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Cubemap* newTexture = TextureFactory::CreateCubemapFromFile(name, paths, wrapMode, filterMode);
		if (newTexture != nullptr)
		{
			_cubemaps[name] = newTexture;
			_idsToNames[newTexture->GetID()] = name;
		}
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before adding a texture file (", name, ")");
	}
}

Texture2D*const TextureManager::GetTex2D(const char*const name)
{
	if (_initialized)
	{
		if (_texture2Ds.find(name) != _texture2Ds.end())
			return _texture2Ds[name];

		return nullptr;
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before getting a texture (", name, ")");
	}

	return nullptr;
}

Cubemap*const TextureManager::GetCubemap(const char*const name)
{
	if (_initialized)
	{
		if (_cubemaps.find(name) != _cubemaps.end())
			return _cubemaps[name];

		return nullptr;
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before getting a texture (", name, ")");
	}

	return nullptr;
}

Texture2D*const TextureManager::GetTex2DByID(const ID ID)
{
	if (_idsToNames.find(ID) != _idsToNames.end())
		return _texture2Ds[_idsToNames[ID]];

	return nullptr;
}

Cubemap*const TextureManager::GetCubemapByID(const ID ID)
{
	if (_idsToNames.find(ID) != _idsToNames.end())
		return _cubemaps[_idsToNames[ID]];

	return nullptr;
}

void TextureManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _texture2Ds)
			SafeDelete(item.second);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the texture manager as it was not initialized!");
	}
}