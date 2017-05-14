/*
===========================================================================
FontManager.h

Defines a class responsible for managing Font objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <vector>
#include "Font.h"

namespace s3dge
{
	class FontManager
	{
	private:
		static std::vector<Font*> _fonts;
		static bool _initialized;

	public:
		static void Initialize();
		static void Add(cstring name, cstring path, float size, bool overrideExisting = false);
		static Font* Get(cstring name);
		static void Dispose();

	private:
		FontManager();
		FontManager(const FontManager& tRef) = delete;
		FontManager& operator = (const FontManager& tRef) = delete;
		~FontManager(void) {}
	};
}