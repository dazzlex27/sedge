/*
===========================================================================
Layer.cpp

A class designed to represent a layer of objects on screen.
Each layer requires a shader instance and a renderer instance.

Using layers is highly encouraged, event if there's only one. That helps to keep things clean.
===========================================================================
*/

#include "Layer.h"
#include "Graphics/Renderables/Mesh.h"
#include "Graphics/Renderables/Renderable.h"
#include "Graphics/Renderers/Renderer3D.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "System/DeleteMacros.h"

using namespace s3dge;

Layer::Layer(ShaderProgram* shaderProgram)
{
	_transformationMatrix = Matrix4::GetIdentity();
	_shaderProgram = shaderProgram;
	_renderer = new Renderer3D();
	_ownsRenderer = true;
	_ownsShader = false;
}

Layer::Layer(ShaderProgram* shaderProgram, Renderer* renderer)
{
	_transformationMatrix = Matrix4::GetIdentity();
	_shaderProgram = shaderProgram;
	_renderer = renderer;
	_ownsRenderer = false;
	_ownsShader = false;
}

Layer::~Layer()
{
	Dispose();
}

void Layer::Add(Renderable* renderable)
{
	_renderables.push_back(renderable);
}

void Layer::Draw()
{
	_shaderProgram->Bind();
	_renderer->Begin();

	for (const auto renderable : _renderables)
		renderable->Submit(_renderer);
	
	_renderer->End();
	_renderer->Flush();
}

void Layer::Dispose()
{
	if (_ownsShader)
		SafeDelete(_shaderProgram);
	
	if (_ownsRenderer)
		SafeDelete(_renderer);
}

Layer& Layer::operator=(const Layer& other)
{
	Dispose();
	return *this;
}

void Layer::SetShaderProgram(ShaderProgram* shaderProgram)
{
	if (_ownsShader)
		SafeDelete(_shaderProgram);

	_shaderProgram = shaderProgram;
	_ownsShader = false;
}

void Layer::SetRenderer(Renderer* renderer)
{
	if (_ownsRenderer)
		SafeDelete(_renderer);

	_ownsRenderer = false;
	_renderer = renderer;
}

void Layer::SetTransformationMatrix(Matrix4 matrix)
{
	_transformationMatrix = matrix;
}