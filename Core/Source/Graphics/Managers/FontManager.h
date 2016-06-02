/*
===========================================================================
FontManager.h

Defines a class responsible for managing Font objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>

namespace s3dge
{
	class Font;

	class FontManager
	{
	private:
		static std::map<std::string, Font*> _fonts;
		static bool _initialized;

	public:
		static void Initialize();
		static void Add(const char*const name, const char*const path, const float size, const bool overrideExisting = false);
		static Font* Get(const char*const name);
		static void Dispose();

	private:
		FontManager();
		FontManager(const FontManager& tRef) = delete;
		FontManager& operator = (const FontManager& tRef) = delete;
		~FontManager(void) {}
	};
}