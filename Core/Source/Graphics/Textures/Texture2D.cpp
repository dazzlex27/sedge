/*
===========================================================================
Texture.cpp

implements the Texture2D class
===========================================================================
*/

#include "Texture2D.h"
#include <GL/glew.h>
#include "Graphics/GraphicsAPI.h"
#include "System/ImageUtils.h"
#include "System/Log.h"

using namespace s3dge;

static int GetChannelsCode(int channelCount);
static int GetWrapModeValue(TextureWrapMode wrapMode);
static int GetFilterModeValue(TextureFilterMode filterMode);

Texture2D::Texture2D(const char* name, const char* path, TextureType type, TextureWrapMode wrapMode, TextureFilterMode filterMode)
	: Texture(name, path, TextureTarget::Tex2D, wrapMode, filterMode), _type(type)
{
}

bool Texture2D::Load()
{
	const int wrapMode = GetWrapModeValue(WrapMode);
	const int filterMode = GetFilterModeValue(FilterMode);

	byte* imagePixels = ImageUtils::LoadImage(Path.c_str(), &_width, &_height, &_components);

	if (!imagePixels)
	{
		LOG_ERROR("Failed to load texture \"", Name.c_str(), "\"");
		ImageUtils::ReleaseImage(imagePixels);
		return false;
	}

	Bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GetChannelsCode(_components), GL_UNSIGNED_BYTE, imagePixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	GraphicsAPI::GenerateMipmap(Target);

	Unbind();

	ImageUtils::ReleaseImage(imagePixels);

	return true;
}

void Texture2D::SetWrapMode(TextureWrapMode wrapMode)
{
	WrapMode = wrapMode;

	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetWrapModeValue(wrapMode));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetWrapModeValue(wrapMode));
	Unbind();
}

void Texture2D::SetFilterMode(TextureFilterMode filterMode)
{
	FilterMode = filterMode;

	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetFilterModeValue(filterMode));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetFilterModeValue(filterMode));
	Unbind();
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