/*
===========================================================================
Layer.cpp

A class designed to represent a layer of objects on screen.
Each layer requires a shader instance and a renderer instance.

Using layers is highly encouraged, event if there's only one. That helps to keep things clean.
===========================================================================
*/

#include "Layer.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace graphics;
	
//Layer::Layer()
//{
	// TODO: create default shader to implement here.
	//_transformationMatrix = math::mat4::GetIdentity();
	//_shaderProgram = new ShaderProgram();
	//_renderer = new Renderer2D();
	// _ownsRenderer = true;
	// _ownsShader = true;
//}

Layer::Layer(ShaderProgram* shaderProgram)
{
	_transformationMatrix = math::mat4::GetIdentity();
	_shaderProgram = shaderProgram;
	_renderer = new Renderer2D();
	_ownsRenderer = true;
	_ownsShader = false;
}

Layer::Layer(ShaderProgram* shaderProgram, Renderer2D* renderer)
{
	_transformationMatrix = math::mat4::GetIdentity();
	_shaderProgram = shaderProgram;
	_renderer = renderer;
	_ownsRenderer = false;
	_ownsShader = false;
}

Layer::~Layer()
{
	Dispose();
}

void Layer::Add(Renderable2D* renderable)
{
	_renderables.push_back(renderable);
}

void Layer::Render()
{
	_shaderProgram->Enable();
	_renderer->Begin();

	for (const Renderable2D* renderable : _renderables)
		renderable->Submit(_renderer);
	
	_renderer->End();
	_renderer->Flush();
}

void Layer::Dispose()
{
	//for (uint i = 0; i < _renderables.size(); ++i)
	//	SafeDelete(_renderables[i]);

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

void Layer::SetRenderer(Renderer2D* renderer)
{
	if (_ownsRenderer)
		SafeDelete(_renderer);

	_ownsRenderer = false;
	_renderer = renderer;
}

void Layer::SetTransformationMatrix(math::mat4 matrix)
{
	_transformationMatrix = matrix;
}