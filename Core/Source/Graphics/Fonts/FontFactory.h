/*
===========================================================================
FontFactory.h

Takes responsibility for creating Font objects
===========================================================================
*/

#pragma once

#include "Font.h"

namespace s3dge
{
	class FontFactory
	{
	public:
		static Font* CreateDefaultFont();
		static Font* CreateFont(const char* name, const char* path, float size);

	private:
		FontFactory();
		FontFactory(const FontFactory& tRef) = delete;
		FontFactory& operator = (const FontFactory& tRef) = delete;
		~FontFactory(void) {}
	};
}