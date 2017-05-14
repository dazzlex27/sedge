/*
===========================================================================
Font.h

Defines a class responsible for processing text charachters.

* relies on FreeType and FreeType-GL
===========================================================================
*/

#pragma once

#include <string>

#include "CustomTypes.h"

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
		cstring _name;
		cstring _path;
		float _size;
		ftgl::texture_atlas_t* _atlas;
		ftgl::texture_font_t* _font;

	public:
		Font(cstring name, cstring path, float size);
		~Font();

		uint GetAtlasID() const;
		inline ftgl::texture_font_t* GetFontFace() const { return _font; }
		inline cstring GetName() const { return _name; }

	private:
		bool Initialize();
		void LoadFontFromFile();
	};
}