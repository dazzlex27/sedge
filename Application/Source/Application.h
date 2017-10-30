#pragma once

#include <S3DGEngine.h>

class Application : public s3dge::S3DGEngine
{
private:
	s3dge::Scene* _mainScene;
	s3dge::Layer2D* _hudLayer;
	s3dge::Camera* _camera;

public:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Dispose() override;

private:
	inline void DrawUI();
	inline void DrawSkybox(const s3dge::Matrix4& viewMatrix);
	inline void DrawScene(const s3dge::Matrix4& viewMatrix);
};