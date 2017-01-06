/*
===========================================================================
Font.cpp

implements the font class
===========================================================================
*/

#include "Font.h"
#include "Internal/Log.h"
#include "Internal/DeleteMacros.h"
#include "Utilities/FileUtils.h"

namespace s3dge
{
	namespace Graphics
	{
		Font::Font(cstring name, cstring path, float size)
			: _name(name), _path(path), _size(size)
		{
			if (!Initialize())
				LOG_ERROR("Failed to load font: ", name);
		}

		bool Font::Initialize()
		{
			if (!FileUtils::CheckFileExists(_path))
				return false;

			LoadFontFromFile();
			return true;
		}

		void Font::LoadFontFromFile()
		{
			_atlas = ftgl::texture_atlas_new(512, 512, 2);
			_font = ftgl::texture_font_new_from_file(_atlas, _size, _path);
		}

		Font::~Font()
		{
			SafeDelete(_atlas);
			SafeDelete(_font);
		}
	}
}