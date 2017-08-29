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
using namespace std;

std::vector<Texture2D*> TextureManager::_texture2Ds;
std::vector<Cubemap*> TextureManager::_cubemaps;
bool TextureManager::_initialized;

void TextureManager::Initialize()
{
	//_textures.push_back(TextureFactory::CreateDefaultTexture());
	_initialized = true;
}

void TextureManager::AddTex2D(const char* name, const char* path, const TextureWrapMode wrapMode, const TextureFilterMode filterMode, const bool overrideExisting)
{
	if (_initialized)
	{
		if (GetTex2D(name) != nullptr)
		{
			if (overrideExisting)
			{
				Texture2D* newTexture = TextureFactory::CreateTexture2DFromFile(name, path, wrapMode, filterMode);
				if (newTexture != nullptr)
					_texture2Ds.push_back(newTexture);
			}
			else
			{
				LOG_WARNING("Texture \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Texture2D* newTexture = TextureFactory::CreateTexture2DFromFile(name, path, wrapMode, filterMode);
		if (newTexture != nullptr)
			_texture2Ds.push_back(newTexture);
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before adding a texture file (", name, ")");
	}
}

void TextureManager::AddCubemap(const char* name, const vector<const char*>& paths, const TextureWrapMode wrapMode, const TextureFilterMode filterMode, const bool overrideExisting)
{
	if (_initialized)
	{
		if (GetCubemap(name) != nullptr)
		{
			if (overrideExisting)
			{
				Cubemap* newTexture = TextureFactory::CreateCubemapFromFile(name, paths, wrapMode, filterMode);
				if (newTexture != nullptr)
					_cubemaps.push_back(newTexture);
			}
			else
			{
				LOG_WARNING("Texture \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Cubemap* newTexture = TextureFactory::CreateCubemapFromFile(name, paths, wrapMode, filterMode);
		if (newTexture != nullptr)
			_cubemaps.push_back(newTexture);
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before adding a texture file (", name, ")");
	}
}

Texture2D*const TextureManager::GetTex2D(const char* name)
{
	if (_initialized)
	{
		for (auto item : _texture2Ds)
			if (strcmp(item->GetName(), name) == 0)
				return item;
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before getting a texture2D (", name, ")");
	}

	return nullptr;
}

Cubemap*const TextureManager::GetCubemap(const char* name)
{
	if (_initialized)
	{
		for (auto item : _cubemaps)
			if (strcmp(item->GetName(), name) == 0)
				return item;
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before getting a cubemap (", name, ")");
	}

	return nullptr;
}

void TextureManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _texture2Ds)
			SafeDelete(item);

		for (auto item : _cubemaps)
			SafeDelete(item);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the texture manager as it was not initialized!");
	}
}