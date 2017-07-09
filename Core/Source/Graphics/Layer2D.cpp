/*
===========================================================================
Layer2D.cpp

A class designed to represent a layer of objects on screen.
Each layer requires a shader instance and a renderer instance.

Using layers is highly encouraged, event if there's only one. That helps to keep things clean.
===========================================================================
*/

#include "Layer2D.h"
#include "Graphics/Renderables/Mesh.h"
#include "Graphics/Renderables/Renderable2D.h"
#include "Graphics/Renderers/Renderer2D.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "System/DeleteMacros.h"

using namespace s3dge;

//Layer::Layer()
//{
// TODO: create default shader to implement here.
//_transformationMatrix = mat4::GetIdentity();
//_shaderProgram = new ShaderProgram();
//_renderer = new Renderer2D();
// _ownsRenderer = true;
// _ownsShader = true;
//}

Layer2D::Layer2D(ShaderProgram* shaderProgram)
{
	_transformationMatrix = Matrix4::GetIdentity();
	_shaderProgram = shaderProgram;
	_renderer = new Renderer2D();
	_ownsRenderer = true;
	_ownsShader = false;
}

Layer2D::Layer2D(ShaderProgram* shaderProgram, Renderer2D* renderer)
{
	_transformationMatrix = Matrix4::GetIdentity();
	_shaderProgram = shaderProgram;
	_renderer = renderer;
	_ownsRenderer = false;
	_ownsShader = false;
}

Layer2D::~Layer2D()
{
	Dispose();
}

void Layer2D::Add(Renderable2D* renderable)
{
	_renderables.push_back(renderable);
}

void Layer2D::AddMesh(Mesh* mesh)
{
	_renderer->SubmitMesh(mesh);
}

void Layer2D::Render()
{
	_shaderProgram->Enable();
	_renderer->Begin();

	for (const auto renderable : _renderables)
		renderable->Submit(_renderer);

	_renderer->End();
	_renderer->Flush();
}

void Layer2D::Dispose()
{
	//for (uint i = 0; i < _renderables.size(); ++i)
	//	SafeDelete(_renderables[i]);

	if (_ownsShader)
		SafeDelete(_shaderProgram);

	if (_ownsRenderer)
		SafeDelete(_renderer);
}

Layer2D& Layer2D::operator=(const Layer2D& other)
{
	Dispose();
	return *this;
}

void Layer2D::SetShaderProgram(ShaderProgram* shaderProgram)
{
	if (_ownsShader)
		SafeDelete(_shaderProgram);

	_shaderProgram = shaderProgram;
	_ownsShader = false;
}

void Layer2D::SetRenderer(Renderer2D* renderer)
{
	if (_ownsRenderer)
		SafeDelete(_renderer);

	_ownsRenderer = false;
	_renderer = renderer;
}

void Layer2D::SetTransformationMatrix(Matrix4 matrix)
{
	_transformationMatrix = matrix;
}