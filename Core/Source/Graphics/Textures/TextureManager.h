/*
===========================================================================
TextureManager.h

Defines a class responsible for managing Texture objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <vector>
#include "Texture2D.h"

namespace s3dge
{
	class TextureManager
	{
	private:
		static std::vector<Texture2D*> _textures;
		static bool _initialized;

	public:
		static void Initialize();
		static void Add(const char* name, const char* path, TextureWrapMode wrapMode = REPEAT, TextureFilterMode filterModebool = LINEAR, bool overrideExisting = false);
		static Texture2D* Get(const char* name);
		static void Dispose();

		static inline uint GetCount() { return _textures.size(); }

	private:
		TextureManager();
		TextureManager(const TextureManager& tRef) = delete;
		TextureManager& operator = (const TextureManager& tRef) = delete;
		~TextureManager(void) {}
	};
}