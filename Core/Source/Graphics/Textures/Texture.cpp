/*
===========================================================================
Texture.cpp

Implements Texture class.
===========================================================================
*/

#include "Texture.h"
#include "Graphics/GraphicsAPI.h"

using namespace s3dge;

Texture::Texture(const char* name, const char* path, const TextureTarget target, const TextureWrapMode wrapMode, const TextureFilterMode filterMode)
	: Name(name), Path(path), Target(target), WrapMode(wrapMode), FilterMode(filterMode)
{
	GraphicsAPI::GenTextures(1, &ID);
}

Texture::~Texture()
{
	GraphicsAPI::DeleteTextures(1, &ID);
}

void Texture::Bind() const
{
	GraphicsAPI::BindTexture(Target, ID);
}

void Texture::Unbind() const
{
	GraphicsAPI::BindTexture(Target, 0);
}

void Texture::ActivateTexture(const uint num)
{
	GraphicsAPI::ActivateTexture(num);
}

void Texture::BindById(const TextureTarget target, const id texId)
{
	GraphicsAPI::BindTexture(target, texId);
}
