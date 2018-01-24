#pragma once

namespace s3dge
{
	class FontManager;
	class ShaderManager;
	class TextureManager;
	class Renderable2DManager;
	class Renderable3DManager;

	class GraphicsAssetManagerFactory
	{
	public:
		FontManager*const CreateFontManager() const;
		ShaderManager*const CreateShaderManager() const;
		TextureManager*const CreateTextureManager() const;
		Renderable2DManager*const CreateRenderable2DManager() const;
		Renderable3DManager*const CreateRenderable3DManager() const;
	};
}