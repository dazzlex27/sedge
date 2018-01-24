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
		std::map<std::string, Texture2D*> _texture2Ds;
		std::map<std::string, Cubemap*> _cubemaps;
		std::map<ID, std::string> _idsToNames;

	public:
		~TextureManager();
		void AddTex2D(const char*const name, const char*const path, const TextureType type = Diffuse, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterModebool = Linear, const bool overrideExisting = false);
		void AddCubemap(const char*const name, const std::vector<std::string>& paths, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear, const bool overrideExisting = false);
		Texture2D*const GetTex2D(const char*const name);
		Cubemap*const GetCubemap(const char*const name);

		inline uint GetCount() { return _texture2Ds.size(); }

	private:
		TextureManager() {}
		TextureManager(const TextureManager& tRef) = delete;
		TextureManager& operator = (const TextureManager& tRef) = delete;

		friend class GraphicsAssetManagerFactory;
	};
}