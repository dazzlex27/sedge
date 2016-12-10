#pragma once

#include <vector>
#include "Texture.h"

namespace s3dge
{
	namespace Graphics
	{
		class TextureManager
		{
		private:
			static std::vector<Texture*> _textures;

		public:
			static void Initialize();
			static void Add(Texture* texture);
			static void Add(cstring name, cstring path);
			static Texture* Get(cstring name);
			static void Dispose();

			static inline uint GetCount() { return _textures.size(); }

		private:
			TextureManager();
			TextureManager(const TextureManager& tRef) = delete;				// Disable copy constructor.
			TextureManager& operator = (const TextureManager& tRef) = delete;	// Disable assignment operator.
			~TextureManager(void) {}
		};
	}
}