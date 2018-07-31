/*
===========================================================================
Layer2D.cpp

A class designed to represent a Layer2D of objects on screen.
Each Layer2D requires a shader instance and a renderer instance.
===========================================================================
*/

#include "Layer2D.h"
#include "Graphics/Renderables/Renderable2D.h"
#include "Graphics/Renderers/Renderer2D.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "System/MemoryManagement.h"
#include "Graphics/Renderables/Label.h"

using namespace s3dge;

Layer2D::Layer2D(ShaderProgram* shaderProgram)
{
	_transformationMatrix = Matrix4::GetIdentity();
	_shaderProgram = shaderProgram;
	_renderer = new Renderer2D();
}

Layer2D::Layer2D(ShaderProgram* shaderProgram, Renderer2D* renderer)
{
	_transformationMatrix = Matrix4::GetIdentity();
	_shaderProgram = shaderProgram;
	_renderer = renderer;
}

Layer2D::~Layer2D()
{
	SafeDelete(_shaderProgram);
	SafeDelete(_renderer);
}

void Layer2D::Add(Renderable2D*const renderable)
{
	_renderables.push_back(renderable);
}

void Layer2D::Draw()
{
	_shaderProgram->Bind();
	_renderer->Begin();

	for (const Renderable2D* renderable : _renderables)
		renderable->Submit(_renderer);
	
	_renderer->End();
	_renderer->Flush();
}

void Layer2D::SetShaderProgram(ShaderProgram*const shaderProgram)
{
	SafeDelete(_shaderProgram);

	_shaderProgram = shaderProgram;
}

void Layer2D::SetRenderer(Renderer2D*const renderer)
{
	SafeDelete(_renderer);

	_renderer = renderer;
}

void Layer2D::SetTransformationMatrix(const Matrix4& matrix)
{
	_transformationMatrix = matrix;
}