#pragma once

#include <vector>
#include "Texture.h"

namespace S3DGE
{
	namespace Graphics
	{
		class TextureManager
		{
		private:
			static std::vector<Texture*> m_Textures;

		public:
			static void AddTexture(Texture* texture);
			static Texture* GetTexture(cstring name);
			static void Dispose();

			static inline uint GetCount() { return m_Textures.size(); }

		private:
			TextureManager(void);
			TextureManager(const TextureManager& tRef) = delete;				// Disable copy constructor.
			TextureManager& operator = (const TextureManager& tRef) = delete;	// Disable assignment operator.
			~TextureManager(void) {}
		};
	}
}