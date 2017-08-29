/*
===========================================================================
TextureFactory.h

Takes responsibility for creating Texture objects
===========================================================================
*/

#pragma once

#include "Texture2D.h"
#include "Cubemap.h"

namespace s3dge
{
	class TextureFactory
	{
	public:
		static Texture2D* CreateDefaultTexture();
		static Texture2D* CreateTexture2DFromFile(const char* name, const char* path, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);
		static Cubemap* CreateCubemapFromFile(const char* name, const std::vector<const char*>& paths, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);

	private:
		TextureFactory();
		TextureFactory(const TextureFactory& tRef) = delete;
		TextureFactory& operator = (const TextureFactory& tRef) = delete;
		~TextureFactory(void) {}
	};
}