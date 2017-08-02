/*
===========================================================================
Texture.cpp

implements the 2D texture class
===========================================================================
*/

#include "Texture2D.h"
#include <GL/glew.h>
#include "System/ImageUtils.h"
#include "System/DeleteMacros.h"
#include "System/Log.h"

using namespace s3dge;

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
	case REPEAT:
		return GL_REPEAT;
	case MIRRORED_REPEAT:
		return GL_MIRRORED_REPEAT;
	case CLAMP_TO_BORDER:
		return GL_CLAMP_TO_BORDER;
	case CLAMP_TO_EDGE:
		return GL_CLAMP_TO_EDGE;
	}

	return -1; // error
}

static int GetFilterModeValue(TextureFilterMode filterMode)
{
	switch (filterMode)
	{
	case NEAREST:
		return GL_NEAREST;
	case LINEAR:
		return GL_LINEAR;
	case MIPMAP_NEAREST_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;
	case MIPMAP_NEAREST_LINEAR:
		return GL_NEAREST_MIPMAP_LINEAR;
	case MIPMAP_LINEAR_NEAREST:
		return GL_LINEAR_MIPMAP_NEAREST;
	case MIPMAP_LINEAR_LINEAR:
		return GL_LINEAR_MIPMAP_LINEAR;
	}

	return -1; // error
}

Texture2D::Texture2D(cstring name, cstring path, TextureWrapMode wrapMode, TextureFilterMode filterMode)
	: _name(name), _path(path)
{
	_wrapMode = wrapMode;
	_filterMode = filterMode;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_id);
}

bool Texture2D::Load()
{
	int wrapMode = GetWrapModeValue(_wrapMode);
	int filterMode = GetFilterModeValue(_filterMode);

	uint id;

	byte* imagePixels = LoadImage(_path, &_width, &_height, &_components);

	if (imagePixels == nullptr)
		return false;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GetChannelsCode(_components), GL_UNSIGNED_BYTE, imagePixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	SafeDeleteArray(imagePixels);

	_id = id;

	return true;
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::AssignToPosition(const float position)
{
	glActiveTexture(GL_TEXTURE0 + position);
	Bind();
}

void Texture2D::SetWrapMode(TextureWrapMode wrapMode)
{
	_wrapMode = wrapMode;

	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetWrapModeValue(wrapMode));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetWrapModeValue(wrapMode));
	Unbind();
}

void Texture2D::SetFilterMode(TextureFilterMode filterMode)
{
	_filterMode = filterMode;

	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetFilterModeValue(filterMode));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetFilterModeValue(filterMode));
	Unbind();
}