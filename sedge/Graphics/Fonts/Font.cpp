/*
===========================================================================
Font.cpp

implements the font class
===========================================================================
*/

#include "Font.h"
#include <freetype-gl.h>
#include <System/Logger.h>
#include <System/FileUtils.h>
#include <Graphics/GraphicsAPI.h>

using namespace sedge;
using namespace ftgl;

Font::Font(const char* name, const char* path, const float size)
	: _name(name), _path(path), _size(size), _atlas(nullptr), _font(nullptr)
{
}

bool Font::LoadFontFromFile()
{
	_atlas = texture_atlas_new(512, 512, 1);
	if (!_atlas)
		return false;

	_font = texture_font_new_from_file(_atlas, _size, _path.c_str());
	if (!_font)
	{
		LOG_ERROR("Failed to load font from file: ", _path.c_str());
		return false;
	}

	// The font atlas is a single-channel alpha texture, not RGBA
	// We need to upload it with the correct format
	GraphicsAPI::UploadFontAtlasTexture(_atlas->id, _atlas->width, _atlas->height, _atlas->data);

	return true;
}

const uint Font::GetAtlasID() const 
{ 
	if (_atlas)
		return _atlas->id;
	return 0;
}

Font::~Font()
{
	if (_font)
		texture_font_delete(_font);
	if (_atlas)
		texture_atlas_delete(_atlas);
}