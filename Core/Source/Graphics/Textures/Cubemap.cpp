/*
===========================================================================
Cubemap.cpp

implements the Cubemap class
===========================================================================
*/

#include "Cubemap.h"
#include <GL/glew.h>
#include "System/ImageUtils.h"
#include "System/DeleteMacros.h"
#include "System/Log.h"

using namespace s3dge;
using namespace std;

static int GetChannelsCode(int channelCount);
static int GetWrapModeValue(TextureWrapMode wrapMode);
static int GetFilterModeValue(TextureFilterMode filterMode);

Cubemap::Cubemap(const char* name, const vector<const char*>& paths, const TextureWrapMode wrapMode, const TextureFilterMode filterMode)
	: _paths(paths), Texture(name, paths[0], TextureTarget::Cube, wrapMode, filterMode)
{
}

void Cubemap::Bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void Cubemap::Unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

bool Cubemap::Load()
{
	const int wrapMode = GetWrapModeValue(WrapMode);
	const int filterMode = GetFilterModeValue(FilterMode);

	int width;
	int height;
	int components;

	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	for (uint i = 0; i < _paths.size(); i++)
	{
		byte* imagePixels = ImageUtils::LoadImage(_paths[i], &width, &height, &components);

		if (!imagePixels)
		{
			LOG_ERROR("Failed to load texture \"", Name.c_str(), "\"");
			ImageUtils::ReleaseImage(imagePixels);
			return false;
		}
		
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagePixels);
		ImageUtils::ReleaseImage(imagePixels);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrapMode);
	
	return true;
}

static int GetChannelsCode(int channelCount)
{
	switch (channelCount)
	{
	case 1:
		return GL_LUMINANCE;
	case 3:
		return GL_RGB;
	case 4:
		return GL_RGBA;
	}

	return -1; // error
}

static int GetWrapModeValue(TextureWrapMode wrapMode)
{
	switch (wrapMode)
	{
	case Repeat:
		return GL_REPEAT;
	case MirroredRepeat:
		return GL_MIRRORED_REPEAT;
	case ClampToBorder:
		return GL_CLAMP_TO_BORDER;
	case ClampToEdge:
		return GL_CLAMP_TO_EDGE;
	}

	return -1; // error
}

static int GetFilterModeValue(TextureFilterMode filterMode)
{
	switch (filterMode)
	{
	case Nearest:
		return GL_NEAREST;
	case Linear:
		return GL_LINEAR;
	case NearestMipmapNearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	case NearestMipmapLinear:
		return GL_NEAREST_MIPMAP_LINEAR;
	case LinearMipmapNearest:
		return GL_LINEAR_MIPMAP_NEAREST;
	case LinearMipmapLinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	}

	return -1; // error
}