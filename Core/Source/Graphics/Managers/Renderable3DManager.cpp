/*
===========================================================================
Renderable3DManager.cpp

Implements the Renderable3DManager class.
===========================================================================
*/

#include "Renderable3DManager.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

#include "Graphics/Renderables/Mesh.h"
#include "Graphics/Renderables/Model.h"
#include "Graphics/Renderables/Skybox.h"

using namespace s3dge;
using namespace std;

map<string, Mesh*> Renderable3DManager::_meshes;
map<string, Model*> Renderable3DManager::_models;
map<string, Skybox*> Renderable3DManager::_skyboxes;
bool Renderable3DManager::_initialized;

void Renderable3DManager::Initialize()
{
	if (!_initialized)
	{
		_initialized = true;
	}
	else
	{
		LOG_WARNING("Renderable3D manager has already been initialized");
	}
}

void Renderable3DManager::AddMesh(const char*const name, Mesh*const mesh, const bool overwrite)
{
	if (_initialized)
	{
		if (GetMesh(name) == nullptr)
			_meshes[name] = mesh;
		else
		{
			if (overwrite)
				_meshes[name] = mesh;
			else
				LOG_WARNING("Mesh \"", name, "\" already exists and will not be overwritten");
		}
	}
	else
		LOG_WARNING("Renderable3D manager was not initialized before adding a mesh (", name, ")");
}

void Renderable3DManager::AddModel(const char*const name, Model*const model, const bool overwrite)
{
	if (_initialized)
	{
		if (GetModel(name) == nullptr)
			_models[name] = model;
		else
		{
			if (overwrite)
				_models[name] = model;
			else
				LOG_WARNING("Model \"", name, "\" already exists and will not be overwritten");
		}
	}
	else
		LOG_WARNING("Renderable3D manager was not initialized before adding a model (", name, ")");
}

void Renderable3DManager::AddSkybox(const char*const name, Skybox*const skybox, const bool overwrite)
{
	if (_initialized)
	{
		if (GetSkybox(name) == nullptr)
			_skyboxes[name] = skybox;
		else
		{
			if (overwrite)
				_skyboxes[name] = skybox;
			else
				LOG_WARNING("Skybox \"", name, "\" already exists and will not be overwritten");
		}
	}
	else
		LOG_WARNING("Renderable3D manager was not initialized before adding a skybox (", name, ")");
}

Mesh*const Renderable3DManager::GetMesh(const char*const name)
{
	if (_meshes.find(name) != _meshes.end())
		return _meshes[name];

	return nullptr;
}

Model*const Renderable3DManager::GetModel(const char*const name)
{
	if (_models.find(name) != _models.end())
		return _models[name];

	return nullptr;
}

Skybox*const Renderable3DManager::GetSkybox(const char*const name)
{
	if (_skyboxes.find(name) != _skyboxes.end())
		return _skyboxes[name];

	return nullptr;
}

void Renderable3DManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _meshes)
			SafeDelete(item.second);
		for (auto item : _models)
			SafeDelete(item.second);
		for (auto item : _skyboxes)
			SafeDelete(item.second);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the Renderable3D manager as it was not initialized!");
	}
}