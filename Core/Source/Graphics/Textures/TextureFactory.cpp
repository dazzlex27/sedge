/*
===========================================================================
TextureFactory.cpp

Implements TextureFactory class
===========================================================================
*/

#include "TextureFactory.h"
#include "System/FileUtils.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;

Texture2D* TextureFactory::CreateDefaultTexture()
{
	return nullptr;
}

Texture2D* TextureFactory::CreateTextureFromFile(const char* name, const char* path, TextureWrapMode wrapMode, TextureFilterMode filterMode)
{
	if (strcmp(name, "") == 0)
	{
		LOG_ERROR("Cannot create a texture with an empty name string");
		return nullptr;
	}

	if (strcmp(path, "") == 0)
	{
		LOG_ERROR("Cannot create a texture with an empty path string");
		return nullptr;
	}

	if (!FileUtils::CheckFileExists(path))
	{
		LOG_ERROR("Texture file \"", path, "\"was not found");
		return nullptr;
	}

	Texture2D* texture = new Texture2D(name, path, wrapMode, filterMode);

	if (!texture->Load())
	{
		LOG_ERROR("Failed to load texture: ", name);
		SafeDelete(texture);
		return nullptr;
	}

	return texture;
}
