/*
===========================================================================
ImageUtils.h

Declares image IO and processing functions.
At the moment only includes image loading. A lot of stuff to do here.
===========================================================================
*/

#pragma once

#include <string.h>
#include "CustomTypes.h"

namespace s3dge
{
	class ImageUtils
	{
	public:
		static byte* LoadImage(const char* path, int* width, int* height, int* components);
		static void ReleaseImage(void* data);
	};
}