#pragma once

#include <S3DGEngine.h>

class Application : public s3dge::S3DGEngine
{
private:
	s3dge::graphics::Layer* _sceneLayer;
	s3dge::graphics::Layer* _hudLayer;
	s3dge::graphics::ShaderProgram* _shaderScene;
	s3dge::graphics::ShaderProgram* _shaderHUD;
	s3dge::Camera* _camera;
	float horizontalAngle;
	float verticalAngle;
	float _lastX;
	float _lastY;

public:
	void Initialize() override;
	void UpdateInput() override;
	void Render() override;
	void Dispose() override;
};