#include "TextureManager.h"

namespace s3dge
{
	namespace Graphics
	{
		std::vector<Texture*> TextureManager::_textures;
		bool TextureManager::_initialized;

		void TextureManager::Initialize()
		{
			_initialized = true;
		}

		void TextureManager::Add(cstring name, cstring path, bool overrideExisting)
		{
			if (_initialized)
			{
				if (Get(name) != nullptr)
					if (overrideExisting)
					{
						_textures.push_back(new Texture(name, path));
						return;
					}
					else
					{
						return;
					}

				_textures.push_back(new Texture(name, path));
			}
		}

		Texture* TextureManager::Get(cstring name)
		{
			if (_initialized)
			{
				for (auto item : _textures)
					if (item->GetName() == name)
						return item;
			}

			return nullptr;
		}

		void TextureManager::Dispose()
		{
			if (_initialized)
			{
				for (auto item : _textures)
					SafeDelete(item);

				_initialized = false;
			}
		}
	}
}