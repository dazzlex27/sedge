/*
===========================================================================
FontFactory.h

Takes responsibility for creating Font objects
===========================================================================
*/

#pragma once

#include "Font.h"

namespace sedge
{
	class FontFactory
	{
	public:
		static Font* CreateFont(const char*const name, const char*const path, const float size);

	private:
		FontFactory();
		FontFactory(const FontFactory& tRef) = delete;
		FontFactory& operator = (const FontFactory& tRef) = delete;
		~FontFactory(void) {}
	};
}