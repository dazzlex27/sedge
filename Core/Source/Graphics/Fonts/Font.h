/*
===========================================================================
Font.h

Defines a class responsible for processing text charachters.

* relies on FreeType and FreeType-GL
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include <string>

namespace ftgl
{
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace s3dge
{
	class Font
	{
	private:
		std::string _name;
		std::string _path;
		const float _size;
		ftgl::texture_atlas_t* _atlas;
		ftgl::texture_font_t* _font;

	public:
		Font(const char* name, const char* path, const float size);
		~Font();

		const uint GetAtlasID() const;
		inline ftgl::texture_font_t* GetFontFace() const { return _font; }
		inline const char* GetName() const { return _name.c_str(); }
		inline const float GetScaleX() const { return 50.0f; }
		inline const float GetScaleY() const { return 50.0f; }

	private:
		bool Initialize();
		void LoadFontFromFile();
	};
}