/*
===========================================================================
TextureManager.cpp

Implements the texture manager class.
===========================================================================
*/

#include "TextureManager.h"
#include "Graphics/Textures/TextureFactory.h"
#include "System/Logger.h"
#include "System/MemoryManagement.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/Cubemap.h"

using namespace s3dge;
using namespace std;
	
void TextureManager::AddTex2D(const char*const name, const char*const path, const TextureType type, const TextureWrapMode wrapMode, const TextureFilterMode filterMode, const bool overrideExisting)
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
	}
	else
	{
		Texture2D* newTexture = TextureFactory::CreateTexture2DFromFile(name, path, type, wrapMode, filterMode);
		if (newTexture != nullptr)
		{
			_texture2Ds[name] = newTexture;
			_idsToNames[newTexture->GetID()] = name;
		}
	}
}

void TextureManager::AddCubemap(const char*const name, const std::vector<std::string>& paths, const TextureWrapMode wrapMode, const TextureFilterMode filterMode, const bool overrideExisting)
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
	}
	else
	{
		Cubemap* newTexture = TextureFactory::CreateCubemapFromFile(name, paths, wrapMode, filterMode);
		if (newTexture != nullptr)
		{
			_cubemaps[name] = newTexture;
			_idsToNames[newTexture->GetID()] = name;
		}
	}
}

Texture2D*const TextureManager::GetTex2D(const char*const name)
{
	if (_texture2Ds.find(name) != _texture2Ds.end())
		return _texture2Ds[name];

	return nullptr;
}

Cubemap*const TextureManager::GetCubemap(const char*const name)
{
	if (_cubemaps.find(name) != _cubemaps.end())
		return _cubemaps[name];

	return nullptr;
}

TextureManager::~TextureManager()
{
	for (auto item : _texture2Ds)
		SafeDelete(item.second);
}