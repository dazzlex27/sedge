#pragma once

#include <S3DGEngine.h>

class Application : public s3dge::S3DGEngine
{
private:
	s3dge::graphics::Window* _window;
	s3dge::graphics::Layer* _sceneLayer;
	s3dge::graphics::Layer* _hudLayer;
	s3dge::graphics::ShaderProgram* _shaderScene;
	s3dge::graphics::ShaderProgram* _shaderHUD;
	s3dge::graphics::Mesh2D* _mesh;

public:
	void Initialize() override;
	void UpdateInput() override;
	void Render() override;
	void Dispose() override;
};