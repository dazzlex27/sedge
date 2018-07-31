/*
===========================================================================
Cubemap.cpp

implements the Cubemap class
===========================================================================
*/

#include "Cubemap.h"
#include "System/ImageUtils.h"
#include "System/Logger.h"
#include "Graphics/GraphicsAPI.h"

using namespace s3dge;
using namespace std;

Cubemap::Cubemap(const char*const name, const vector<std::string>& paths, const TextureWrapMode wrapMode, const TextureFilterMode filterMode)
	:  Texture(name, paths[0].c_str(), TexCube, wrapMode, filterMode), _paths(paths)
{
}

bool Cubemap::Load()
{
	int width;
	int height;
	int components;

	Bind();

	for (uint i = 0; i < _paths.size(); i++)
	{
		byte* imagePixels = ImageUtils::LoadImage(_paths[i].c_str(), &width, &height, &components);

		if (!imagePixels)
		{
			LOG_ERROR("Failed to load texture \"", Name.c_str(), "\"");
			ImageUtils::ReleaseImage(imagePixels);
			return false;
		}

		ColorCode format;
		switch (components)
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
		
		GraphicsAPI::LoadCubemapImage(i, 0, format, width, height, 0, format, UnsignedByte, imagePixels);
		ImageUtils::ReleaseImage(imagePixels);
	}

	SetFilterMode(FilterMode);
	SetWrapMode(WrapMode);

	Unbind();
	
	return true;
}