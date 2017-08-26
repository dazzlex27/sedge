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

using namespace s3dge;
using namespace std;

map<string, Mesh*> Renderable3DManager::_meshes;
map<string, Model*> Renderable3DManager::_models;
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

void Renderable3DManager::AddMesh(const char* name, Mesh* mesh, bool overwrite)
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

void Renderable3DManager::AddModel(const char* name, Model* model, bool overwrite)
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

Mesh* Renderable3DManager::GetMesh(const char* name)
{
	if (_meshes.find(name) != _meshes.end())
		return _meshes[name];

	return nullptr;
}

Model* Renderable3DManager::GetModel(const char* name)
{
	if (_models.find(name) != _models.end())
		return _models[name];

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

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the Renderable3D manager as it was not initialized!");
	}
}