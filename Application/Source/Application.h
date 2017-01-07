#pragma once

#include <S3DGE.h>

class Application : public s3dge::S3DGE
{
private:
	s3dge::graphics::Window* _window;
	s3dge::graphics::Layer* _layer;
	s3dge::graphics::Label* _fps;
	s3dge::graphics::ShaderProgram* _shaderProgram;
	s3dge::graphics::Sprite* _rect;

public:
	void Initialize() override;
	void UpdateInput() override;
	void Render() override;
	void Dispose() override;
};