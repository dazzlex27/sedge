#include "TextureManager.h"

namespace s3dge
{
	namespace Graphics
	{
		std::vector<Texture*> TextureManager::_textures;

		void TextureManager::Initialize()
		{

		}

		void TextureManager::Add(Texture* texture)
		{
			_textures.push_back(texture);
		}

		void TextureManager::Add(cstring name, cstring path)
		{
			_textures.push_back(new Texture(name, path));
		}

		Texture* TextureManager::Get(cstring name)
		{
			for (auto item : _textures)
				if (item->GetName() == name)
					return item;

			return nullptr;
		}

		void TextureManager::Dispose()
		{
			for (auto item : _textures)
				SafeDelete(item);
		}
	}
}