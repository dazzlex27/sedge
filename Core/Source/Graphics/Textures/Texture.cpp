#include "Texture.h"
#include "Graphics/RenderSystem.h"

using namespace s3dge;

Texture::Texture(const char* name, const char* path, const TextureTarget target, const TextureWrapMode wrapMode, const TextureFilterMode filterMode)
	: Name(name), Path(path), Target(target), WrapMode(wrapMode), FilterMode(filterMode)
{
	RenderSystem::GenTextures(1, &ID);
}

Texture::~Texture()
{
	RenderSystem::DeleteTextures(1, &ID);
}