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
	namespace graphics
	{
		class TextureFactory
		{
		public:
			static Texture2D* CreateDefaultTexture();
			static Texture2D* CreateTexture(cstring name, cstring path);

		private:
			TextureFactory();
			TextureFactory(const TextureFactory& tRef) = delete;
			TextureFactory& operator = (const TextureFactory& tRef) = delete;
			~TextureFactory(void) {}
		};
	}
}