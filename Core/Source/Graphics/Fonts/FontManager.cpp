#include "FontManager.h"

namespace s3dge
{
	namespace Graphics
	{
		std::vector<Font*> FontManager::_fonts;

		void FontManager::Initialize()
		{

		}

		void FontManager::Add(Font* font)
		{
			_fonts.push_back(font);
		}

		void FontManager::Add(cstring name, cstring path, float size)
		{
			_fonts.push_back(new Font(name, path, size));
		}

		Font* FontManager::Get(cstring name)
		{
			for (auto item : _fonts)
				if (item->GetName() == name)
					return item;

			return nullptr;
		}

		void FontManager::Dispose()
		{
			for (auto item : _fonts)
				SafeDelete(item);
		}
	}
}