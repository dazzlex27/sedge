/*
===========================================================================
TextureFactory.cpp

Implements TextureFactory class
===========================================================================
*/

#include "TextureFactory.h"
#include "System/FileUtils.h"
#include "System/Log.h"
#include "System/MemoryManagement.h"
#include "Texture2D.h"
#include "Cubemap.h"

using namespace s3dge;

Texture2D* TextureFactory::CreateDefaultTexture()
{
	return nullptr;
}

Texture2D* TextureFactory::CreateTexture2DFromFile(const char* name, const char* path, TextureType type, TextureWrapMode wrapMode, TextureFilterMode filterMode)
{
	if (strcmp(name, "") == 0)
	{
		LOG_ERROR("Cannot create a texture with an empty name string");
		return nullptr;
	}

	if (!FileUtils::CheckFileExists(path))
	{
		LOG_ERROR("Texture file \"", path, "\"was not found");
		return nullptr;
	}

	Texture2D* texture = new Texture2D(name, path, type, wrapMode, filterMode);

	if (!texture->Load())
	{
		LOG_ERROR("Failed to load texture: ", name);
		SafeDelete(texture);
		return nullptr;
	}

	return texture;
}

Cubemap* TextureFactory::CreateCubemapFromFile(const char*const name, const std::vector<std::string>& paths, const TextureWrapMode wrapMode, const TextureFilterMode filterMode)
{
	if (strcmp(name, "") == 0)
	{
		LOG_ERROR("Cannot create a texture with an empty name string");
		return nullptr;
	}

	for (uint i = 0; i < paths.size(); i++)
	{
		if (strcmp(paths[i].c_str(), "") == 0)
		{
			LOG_ERROR("Cannot create a texture with an empty path string");
			return nullptr;
		}

		if (!FileUtils::CheckFileExists(paths[i].c_str()))
		{
			LOG_ERROR("Texture file \"", paths[i].c_str(), "\"was not found");
			return nullptr;
		}
	}

	Cubemap* texture = new Cubemap(name, paths, wrapMode, filterMode);
	
	if (!texture->Load())
	{
		LOG_ERROR("Failed to load cubemap: ", name);
		SafeDelete(texture);
		return nullptr;
	}

	return texture;
}