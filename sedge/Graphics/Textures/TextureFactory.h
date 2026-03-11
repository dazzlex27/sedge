/*
===========================================================================
TextureFactory.h

Takes responsibility for creating Texture objects
===========================================================================
*/

#pragma once

#include <vector>
#include <string>
#include "Texture.h"

namespace sedge
{
	class Texture2D;
	class Cubemap;

	class TextureFactory
	{
	public:
		static Texture2D* CreateDefaultTexture();
		static Texture2D* CreateTexture2DFromFile(const char*const name, const char*const path, const TextureType type = Diffuse, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);
		static Cubemap* CreateCubemapFromFile(const char*const name, const std::vector<std::string>& paths, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);

	private:
		TextureFactory();
		TextureFactory(const TextureFactory& tRef) = delete;
		TextureFactory& operator = (const TextureFactory& tRef) = delete;
		~TextureFactory(void) {}
	};
}