/*
===========================================================================
TextureUtils.h

Contains helper functions and enums for textures.
===========================================================================
*/

#pragma once

namespace s3dge
{
	enum TextureType
	{
		Diffuse,
		Specular
	};

	enum TextureWrapMode
	{
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum TextureFilterMode
	{
		NEAREST = 0,
		LINEAR = 1,
		MIPMAP_NEAREST_NEAREST = 2,
		MIPMAP_LINEAR_NEAREST = 3,
		MIPMAP_NEAREST_LINEAR = 4,
		MIPMAP_LINEAR_LINEAR = 5
	};

	int GetChannelsCode(int channelCount);
	int GetWrapModeValue(TextureWrapMode wrapMode);
	int GetFilterModeValue(TextureFilterMode filterMode);
}