/*
===========================================================================
TextureFactory.cpp

Implements TextureFactory class
===========================================================================
*/

#include "TextureFactory.h"
#include "Utilities/FileUtils.h"
#include "Internal/Log.h"

using namespace s3dge;
using namespace graphics;

Texture2D* TextureFactory::CreateDefaultTexture()
{
	return nullptr;
}

Texture2D* TextureFactory::CreateTexture(cstring name, cstring path)
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
		LOG_ERROR("Texture file ", "\"name\"", " was not found");
		return nullptr;
	}

	return new Texture2D(name, path);
}