/*
===========================================================================
Scene.cpp

Implements the Scene class
===========================================================================
*/

#include "Scene.h"
#include "Internal/DeleteMacros.h"
#include "Logic/Objects/Entity.h"
#include "Logic/Objects/Camera.h"

using namespace s3dge;

Scene::Scene()
{
}

Scene::~Scene()
{
	for (uint i = 0; i < _entities.size(); i++)
		SafeDelete(_entities[i]);

	SafeDelete(_camera);
}

void Scene::Update()
{
	for (auto item : _entities)
		item->Update();
}

void Scene::Render()
{
	for (auto item : _entities)
		item->Render();
}

void Scene::AddEntity(Entity* entity)
{
	_entities.push_back(entity);
}

void Scene::RemoveEntity(Entity* entity)
{
	for (uint i = 0; i < _entities.size(); i++)
	{
		if (_entities[i] == entity)
		{
			_entities.erase(_entities.begin() + i);
			break;
		}
	}
}

void Scene::SetCamera(Camera* camera)
{
	_camera = camera;
}