/*
===========================================================================
TextureUtils.cpp

Implements helper functions for textures.

TODO: ditch glew
===========================================================================
*/

#include "TextureUtils.h"
#include <GL/glew.h>

using namespace s3dge;

int s3dge::GetChannelsCode(int channelCount)
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

int s3dge::GetWrapModeValue(TextureWrapMode wrapMode)
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

int s3dge::GetFilterModeValue(TextureFilterMode filterMode)
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