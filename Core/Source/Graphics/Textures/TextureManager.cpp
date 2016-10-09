#include "TextureManager.h"

namespace s3dge
{
	namespace Graphics
	{
		std::vector<Texture*> TextureManager::m_Textures;

		void TextureManager::AddTexture(Texture* texture)
		{
			m_Textures.push_back(texture);
		}

		Texture* TextureManager::GetTexture(cstring name)
		{
			for (auto item : m_Textures)
				if (item->GetName() == name)
					return item;

			return nullptr;
		}

		void TextureManager::Dispose()
		{
			for (auto item : m_Textures)
				SafeDelete(item);
		}
	}
}