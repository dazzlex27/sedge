#pragma once

#include <S3DGE.h>

class Application : public s3dge::S3DGE
{
private:
	s3dge::graphics::Window* _window;
	s3dge::graphics::Layer* _layer;
	s3dge::graphics::ShaderProgram* _shaderProgram;

public:
	void Initialize() override;
	void UpdateInput() override;
	void Render() override;
	void Dispose() override;
};