#pragma once

#include <S3DGE.h>

class Application : public s3dge::S3DGE
{
private:
	s3dge::Graphics::Window* _window;
	s3dge::Graphics::Layer* _layer;
	s3dge::Graphics::Label* _fps;
	s3dge::Graphics::ShaderProgram* _shaderProgram;

public:
	void Initialize() override;
	void UpdateInput() override;
	void Render() override;
	void Dispose() override;

};