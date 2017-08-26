/*
===========================================================================
TextureManager.h

Defines a class responsible for managing Texture objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>
#include "Graphics/Textures/Texture2D.h"

namespace s3dge
{
	class TextureManager
	{
	private:
		static std::map<std::string, Texture2D*> _textures;
		static std::map<id, std::string> _idsToNames;
		static bool _initialized;

	public:
		static void Initialize();
		static void Add(const char* name, const char* path, TextureType type = Diffuse, TextureWrapMode wrapMode = REPEAT, TextureFilterMode filterModebool = LINEAR, bool overrideExisting = false);
		static Texture2D*const Get(const char* name);
		static Texture2D*const GetByID(const id ID);
		static void Dispose();

		static inline uint GetCount() { return _textures.size(); }

	private:
		TextureManager();
		TextureManager(const TextureManager& tRef) = delete;
		TextureManager& operator = (const TextureManager& tRef) = delete;
		~TextureManager(void) {}
	};
}