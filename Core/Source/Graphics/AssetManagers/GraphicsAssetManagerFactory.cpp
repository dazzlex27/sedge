#include "GraphicsAssetManagerFactory.h"
#include "FontManager.h"
#include "Renderable2DManager.h"
#include "Renderable3DManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

using namespace s3dge;

FontManager*const GraphicsAssetManagerFactory::CreateFontManager() const
{
	return new FontManager();
}

ShaderManager*const GraphicsAssetManagerFactory::CreateShaderManager() const
{
	return new ShaderManager();
}

TextureManager*const GraphicsAssetManagerFactory::CreateTextureManager() const
{
	return new TextureManager();
}

Renderable2DManager*const GraphicsAssetManagerFactory::CreateRenderable2DManager() const
{
	return new Renderable2DManager();
}

Renderable3DManager*const GraphicsAssetManagerFactory::CreateRenderable3DManager() const
{
	return new Renderable3DManager();
}