/*
===========================================================================
Font.cpp

implements the font class
===========================================================================
*/

#include "Font.h"
#include <freetype-gl.h>
#include "System/Logger.h"
#include "System/FileUtils.h"

using namespace sedge;
using namespace ftgl;
	
Font::Font(const char* name, const char* path, const float size)
	: _name(name), _path(path), _size(size)
{
}

bool Font::LoadFontFromFile()
{
	_atlas = texture_atlas_new(512, 512, 2);
	_font = texture_font_new_from_file(_atlas, _size, _path.c_str());
	if (!_font)
		return false;

	texture_atlas_upload(_atlas);

	return true;
}

const uint Font::GetAtlasID() const 
{ 
	return _atlas->id; 
}

Font::~Font()
{
	texture_atlas_delete(_atlas);
	texture_font_delete(_font);
}