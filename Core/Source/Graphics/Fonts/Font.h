#pragma once

#include <string>
#include <freetype-gl.h>
#include "Internal/DeleteMacros.h"
#include "Internal/Log.h"
#include "CustomTypes.h"
#include "Utilities/FileIO.h"

namespace s3dge
{
	namespace Graphics
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

			inline uint GetAtlasID() const { return _atlas->id; }
			inline ftgl::texture_font_t* GetFontFace() const { return _font; }
			inline cstring GetName() const { return _name; }

		private:
			bool Initialize();
			void LoadFontFromFile();
		};
	}
}