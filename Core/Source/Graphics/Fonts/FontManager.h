#pragma once

#include <vector>
#include "CustomTypes.h"
#include "Font.h"

namespace s3dge
{
	namespace Graphics
	{
		class FontManager
		{
		private:
			static std::vector<Font*> _fonts;

		public:
			static void Add(cstring name, cstring path, float size);
			static void Add(Font* font);
			static Font* Get(cstring name);
			static void Dispose();

		private:
			FontManager();
			FontManager(const FontManager& tRef) = delete;
			FontManager& operator = (const FontManager& tRef) = delete;
			~FontManager(void) {}
		};
	}
}