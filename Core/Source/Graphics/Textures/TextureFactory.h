/*
===========================================================================
TextureFactory.h

Takes responsibility for creating Texture objects
===========================================================================
*/

#pragma once

#include "Texture2D.h"

namespace s3dge
{
	class TextureFactory
	{
	public:
		static Texture2D* CreateDefaultTexture();
		static Texture2D* CreateTextureFromFile(cstring name, cstring path, TextureWrapMode wrapMode = REPEAT, TextureFilterMode filterMode = LINEAR);

	private:
		TextureFactory();
		TextureFactory(const TextureFactory& tRef) = delete;
		TextureFactory& operator = (const TextureFactory& tRef) = delete;
		~TextureFactory(void) {}
	};
}