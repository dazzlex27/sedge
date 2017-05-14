#pragma once

#include <S3DGEngine.h>

class Application : public s3dge::S3DGEngine
{
private:
	s3dge::Layer* _sceneLayer;
	s3dge::Layer* _hudLayer;
	s3dge::ShaderProgram* _shaderScene;
	s3dge::ShaderProgram* _shaderHUD;
	s3dge::Camera* _camera;
	float horizontalAngle;
	float verticalAngle;

public:
	void Initialize() override;
	void UpdateInput() override;
	void Render() override;
	void Dispose() override;

	void UpdateCamera(const s3dge::Point2D& mousePosition);
};