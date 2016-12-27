#include "FontManager.h"

namespace s3dge
{
	namespace Graphics
	{
		std::vector<Font*> FontManager::_fonts;
		bool FontManager::_initialized;

		void FontManager::Initialize()
		{
			_initialized = true;
		}

		void FontManager::Add(cstring name, cstring path, float size, bool overrideExisting)
		{
			if (_initialized)
			{
				if (Get(name) != nullptr)
					if (overrideExisting)
					{
						_fonts.push_back(new Font(name, path, size));
						return;
					}
					else
					{
						return;
					}

				_fonts.push_back(new Font(name, path, size));
			}
		}

		Font* FontManager::Get(cstring name)
		{
			if (_initialized)
			{
				for (auto item : _fonts)
					if (item->GetName() == name)
						return item;
			}

			return nullptr;
		}

		void FontManager::Dispose()
		{
			for (auto item : _fonts)
				SafeDelete(item);

			_initialized = true;
		}
	}
}