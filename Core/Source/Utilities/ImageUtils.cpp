#include "ImageUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

byte* LoadImage(cstring path, int* width, int* height, int* components)
{
	return stbi_load(path, width, height, components, 0);
}