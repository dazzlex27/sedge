/*
===========================================================================
Texture.cpp

implements the Texture2D class
===========================================================================
*/

#include "Texture2D.h"
#include "Graphics/GraphicsAPI.h"
#include "System/ImageUtils.h"
#include "System/Logger.h"

using namespace sedge;

Texture2D::Texture2D(const char*const name, const char*const path, const TextureType type, const TextureWrapMode wrapMode, const TextureFilterMode filterMode)
	: Texture(name, path, Tex2D, wrapMode, filterMode), _type(type)
{
}

bool Texture2D::Load()
{
	byte* imagePixels = ImageUtils::LoadImage(Path.c_str(), &_width, &_height, &_components);

	if (!imagePixels)
	{
		LOG_ERROR("Failed to load texture \"", Name.c_str(), "\"");
		ImageUtils::ReleaseImage(imagePixels);
		return false;
	}

	ColorCode format;
	switch (_components)
	{
	case 1:
		format = Mono;
		break;
	case 3:
		format = Rgb;
		break;
	case 4:
		format = Rgba;
		break;
	}

	Bind();

	GraphicsAPI::LoadTex2DImage(0, format, _width, _height, 0, format, UnsignedByte, imagePixels);

	SetFilterMode(FilterMode);
	SetWrapMode(WrapMode);

	GraphicsAPI::GenerateMipmap(Target);

	Unbind();

	ImageUtils::ReleaseImage(imagePixels);

	return true;
}