#pragma once

#include "S3DGETypes.h"
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

static byte* LoadImage(cstring path, int* width, int* height, int* components)
{
	return stbi_load(path, width, height, components, 0);
}