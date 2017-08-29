/*
===========================================================================
TextureManager.h

Defines a class responsible for managing Texture objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>
#include <vector>
#include "Graphics/Textures/Texture.h"

namespace s3dge
{
	class Texture2D;
	class Cubemap;

	class TextureManager
	{
	private:
		static std::map<std::string, Texture2D*> _texture2Ds;
		static std::map<std::string, Cubemap*> _cubemaps;
		static std::map<id, std::string> _idsToNames;
		static bool _initialized;

	public:
		static void Initialize();
		static void AddTex2D(const char*const name, const char*const path, TextureType type = Diffuse, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterModebool = Linear, const bool overrideExisting = false);
		static void AddCubemap(const char*const name, const std::vector<std::string>& paths, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear, const bool overrideExisting = false);
		static Texture2D*const GetTex2D(const char*const name);
		static Cubemap*const GetCubemap(const char*const name);
		static Texture2D*const GetTex2DByID(const id ID);
		static Cubemap*const GetCubemapByID(const id ID);
		static void Dispose();

		static inline uint GetCount() { return _texture2Ds.size(); }

	private:
		TextureManager();
		TextureManager(const TextureManager& tRef) = delete;
		TextureManager& operator = (const TextureManager& tRef) = delete;
		~TextureManager(void) {}
	};
}