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
#include "Cubemap.h"

namespace s3dge
{
	class TextureManager
	{
	private:
		static std::vector<Texture2D*> _texture2Ds;
		static std::vector<Cubemap*> _cubemaps;
		static bool _initialized;

	public:
		static void Initialize();
		static void AddTex2D(const char* name, const char* path, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterModebool = Linear, const bool overrideExisting = false);
		static void AddCubemap(const char* name, const std::vector<const char*>& path, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterModebool = Linear, const bool overrideExisting = false);
		static Texture2D*const GetTex2D(const char* name);
		static Cubemap*const GetCubemap(const char* name);
		static void Dispose();

		static inline uint GetCount() { return _texture2Ds.size(); }

	private:
		TextureManager();
		TextureManager(const TextureManager& tRef) = delete;
		TextureManager& operator = (const TextureManager& tRef) = delete;
		~TextureManager(void) {}
	};
}