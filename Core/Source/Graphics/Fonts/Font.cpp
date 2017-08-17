/*
===========================================================================
Font.cpp

implements the font class
===========================================================================
*/

#include "Font.h"
#include <freetype-gl.h>
#include "System/Log.h"
#include "System/DeleteMacros.h"
#include "System/FileUtils.h"

using namespace s3dge;
using namespace ftgl;
	
Font::Font(const char* name, const char* path, const float size)
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
	_atlas = texture_atlas_new(512, 512, 2);
	_font = texture_font_new_from_file(_atlas, _size, _path);
	texture_atlas_upload(_atlas);
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