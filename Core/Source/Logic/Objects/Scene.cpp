/*
===========================================================================
Scene.cpp

Implements the Scene class
===========================================================================
*/

#include "Scene.h"
#include "Entity.h"
#include "Logic/Cameras/Camera.h"
#include "System/DeleteMacros.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Textures/Texture2D.h"

using namespace s3dge;

Scene::Scene(ShaderProgram*const shaderProgram)
{
	_shaderProgram = shaderProgram;
}

void Scene::AddEntity(Entity*const entity)
{
	_entities.push_back(entity);
}

void Scene::RemoveEntity(Entity*const entity)
{
}

void Scene::Update()
{
	for (uint i = 0; i < _entities.size(); i++)
		_entities[i]->Update();

	UpdateCamera();
}

void Scene::Draw()
{
	_shaderProgram->Bind();

	for (uint i = 0; i < _entities.size(); i++)
	{
		_shaderProgram->SetModel(_entities[i]->GetModelMatrix());
		_entities[i]->Draw();
	}
}

void Scene::SetActiveCamera(Camera*const camera)
{
	_activeCamera = camera;
}

void Scene::UpdateCamera()
{
	if (!_activeCamera)
		return;

	_shaderProgram->Bind();
	_shaderProgram->SetProjection(_activeCamera->GetProjection());
	_shaderProgram->SetView(_activeCamera->GetView());
}

Scene::~Scene()
{
	SafeDelete(_shaderProgram);
}