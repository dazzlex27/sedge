#pragma once

#include <S3DGEngine.h>

class Application : public s3dge::S3DGEngine
{
private:
	s3dge::Scene* _mainScene;
	s3dge::Layer2D* _hudLayer;
	s3dge::Camera* _camera;
	s3dge::FontManager* _fontManager;
	s3dge::ShaderManager* _shaderManager;
	s3dge::TextureManager* _textureManager;
	s3dge::Renderable2DManager* _renderable2DManager;
	s3dge::Renderable3DManager* _renderable3DManager;
	s3dge::GraphicsObjectFactorySet _graphicsObjFactorySet;
	s3dge::InputManager* _inputManager;

public:
	void Initialize(const s3dge::InitializationToolset& initToolset) override;
	void UpdateLogic() override;
	void Render() override;
	void Dispose() override;

private:
	inline void DrawUI();
	inline void DrawSkybox(const s3dge::Matrix4& viewMatrix);
	inline void DrawScene(const s3dge::Matrix4& viewMatrix);
	void LoadAssets();
};