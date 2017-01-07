/*
===========================================================================
TextureManager.h

Defines a class responsible for managing Texture objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <vector>
#include "Texture.h"

namespace s3dge
{
	namespace graphics
	{
		class TextureManager
		{
		private:
			static std::vector<Texture*> _textures;
			static bool _initialized;

		public:
			static void Initialize();
			static void Add(cstring name, cstring path, bool overrideExisting = false);
			static Texture* Get(cstring name);
			static void Dispose();

			static inline uint GetCount() { return _textures.size(); }

		private:
			TextureManager();
			TextureManager(const TextureManager& tRef) = delete;
			TextureManager& operator = (const TextureManager& tRef) = delete;
			~TextureManager(void) {}
		};
	}
}