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
	namespace graphics
	{
		class FontFactory
		{
		public:
			static Font* CreateDefaultFont();
			static Font* CreateFont(cstring name, cstring path, float size);

		private:
			FontFactory();
			FontFactory(const FontFactory& tRef) = delete;
			FontFactory& operator = (const FontFactory& tRef) = delete;
			~FontFactory(void) {}
		};
	}
}