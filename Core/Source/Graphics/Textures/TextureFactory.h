/*
===========================================================================
TextureFactory.h

Takes responsibility for creating Texture objects
===========================================================================
*/

#pragma once

#include "Texture.h"

namespace s3dge
{
	namespace graphics
	{
		class TextureFactory
		{
		public:
			static Texture* CreateDefaultTexture();
			static Texture* CreateTexture(cstring name, cstring path);

		private:
			TextureFactory();
			TextureFactory(const TextureFactory& tRef) = delete;
			TextureFactory& operator = (const TextureFactory& tRef) = delete;
			~TextureFactory(void) {}
		};
	}
}