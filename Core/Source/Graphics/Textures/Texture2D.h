/*
===========================================================================
Texture2D.h

Defines a class responsible for processing 2D textures.
===========================================================================
*/

#pragma once

#include "Texture.h"

namespace s3dge
{
	class Texture2D : public Texture
	{
	private:
		int _width;
		int _height;
		int _components;
		TextureType _type;

	private:
		Texture2D(const char*const name, const char*const path, const TextureType type = Diffuse, const TextureWrapMode wrapMode = Repeat, const TextureFilterMode filterMode = Linear);

	public:
		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }
		inline int GetComponentsCount() const { return _components; }
		
	public:
		virtual bool Load() override;

		friend class TextureFactory;
	};
}