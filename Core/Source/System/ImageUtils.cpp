/*
===========================================================================
ImageUtils.cpp

Implements the functions declared in the header file.
Image loading done via stb_image library by Sean T. Barrett.
===========================================================================
*/

#include "ImageUtils.h"

// WARNING! MUST ONLY BE DEFINED ONCE!
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace s3dge;

void ImageUtils::SetFlipVertically(const bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
}

// image loading via stb_image. Supports *.bmp, *.png and whatnot.
byte* ImageUtils::LoadImage(const char* path, int* width, int* height, int* components)
{
	return stbi_load(path, width, height, components, 0);
}

void ImageUtils::ReleaseImage(void* data)
{
	stbi_image_free(data);
}