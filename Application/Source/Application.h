#pragma once

#include <Engine.h>

class Application : public sedge::Engine
{
private:
	sedge::Scene* _mainScene;
	sedge::Layer2D* _hudLayer;
	sedge::FontManager* _fontManager;
	sedge::ShaderFactory* _shaderFactory;
	sedge::TextureManager* _textureManager;
	sedge::Renderable2DManager* _renderable2DManager;
	sedge::Renderable3DManager* _renderable3DManager;
	sedge::GraphicsObjectFactorySet _graphicsObjFactorySet;
	sedge::InputManager* _inputManager;

public:
	Application();
	~Application();

public:
	void Initialize(const sedge::InitializationToolset& initToolset) override;
	void UpdateLogic() override;
	void Render() override;
	void Dispose() override;

private:
	void LoadAssets();
};