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
		std::map<std::string, Font*> _fonts;

	public:
		FontManager() {}
		~FontManager();
		void AddFont(const char*const name, const char*const path, const float size, const bool overrideExisting = false);
		Font*const GetFont(const char*const name);

	private:
		FontManager(const FontManager& tRef) = delete;
		FontManager& operator = (const FontManager& tRef) = delete;

		friend class GraphicsAssetManagerFactory;
	};
}