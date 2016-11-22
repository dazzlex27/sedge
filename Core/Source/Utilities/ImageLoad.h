#pragma once

#include <string.h>
#include "CustomTypes.h"
#include <stb_image.h>

static byte* LoadImage(cstring path, int* width, int* height, int* components)
{
	return stbi_load(path, width, height, components, 0);
}