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

void Texture::BindById(const TextureTarget target, const ID texId)
{
	GraphicsAPI::BindTexture(target, texId);
}

void Texture::SetWrapMode(TextureWrapMode wrapMode)
{
	WrapMode = wrapMode;

	GraphicsAPI::SetTextureWrapMode(Target, WrapS, wrapMode);
	GraphicsAPI::SetTextureWrapMode(Target, WrapT, wrapMode);
	GraphicsAPI::SetTextureWrapMode(Target, WrapR, wrapMode);
}

void Texture::SetFilterMode(TextureFilterMode filterMode)
{
	FilterMode = filterMode;

	GraphicsAPI::SetTextureFilterMode(Target, Min, filterMode);
	GraphicsAPI::SetTextureFilterMode(Target, Mag, filterMode);
}