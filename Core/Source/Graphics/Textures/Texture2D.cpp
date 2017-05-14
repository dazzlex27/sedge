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

int GetWrapModeValue(TextureWrapMode wrapMode)
{
	int mode = 0;

	switch (wrapMode)
	{
	case REPEAT:
		mode = GL_REPEAT;
		break;
	case MIRRORED_REPEAT:
		mode = GL_MIRRORED_REPEAT;
		break;
	case CLAMP_TO_BORDER:
		mode = GL_CLAMP_TO_BORDER;
		break;
	case CLAMP_TO_EDGE:
		mode = GL_CLAMP_TO_EDGE;
		break;
	}

	return mode;
}

int GetFilterModeValue(TextureFilterMode filterMode)
{
	int mode = 0;

	switch (filterMode)
	{
	case NEAREST:
		mode = GL_NEAREST;
		break;
	case LINEAR:
		mode = GL_LINEAR;
		break;
	case MIPMAP_NEAREST_NEAREST:
		mode = GL_NEAREST_MIPMAP_NEAREST;
		break;
	case MIPMAP_NEAREST_LINEAR:
		mode = GL_NEAREST_MIPMAP_LINEAR;
		break;
	case MIPMAP_LINEAR_NEAREST:
		mode = GL_LINEAR_MIPMAP_NEAREST;
		break;
	case MIPMAP_LINEAR_LINEAR:
		mode = GL_LINEAR_MIPMAP_LINEAR;
		break;
	}

	return mode;
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagePixels);

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