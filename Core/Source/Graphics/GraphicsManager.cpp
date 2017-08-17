/*
===========================================================================
GraphicsManager.cpp

Implements the renderables manager class.
===========================================================================
*/

#include "GraphicsManager.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
using namespace std;

map<const char*, Sprite*> GraphicsManager::_sprites;
map<const char*, Label*> GraphicsManager::_labels;
map<const char*, Group*> GraphicsManager::_groups;
map<const char*, Mesh*> GraphicsManager::_meshes;
bool GraphicsManager::_initialized;

void GraphicsManager::Initialize()
{
	if (!_initialized)
	{
		_initialized = true;
	}
	else
	{
		LOG_WARNING("Graphics manager has already been initialized");
	}
}

void GraphicsManager::AddSprite(const char* name, Sprite* sprite, bool overwrite)
{
	if (_initialized)
	{
		if (GetSprite(name) == nullptr)
			_sprites[name] = sprite;
		else
		{
			if (overwrite)
				_sprites[name] = sprite;
			else
				LOG_WARNING("Sprite \"", name, "\" already exists and will not be overwritten");
		}
	}
	else
		LOG_WARNING("Graphics manager was not initialized before adding a sprite (", name, ")");
}

void GraphicsManager::AddLabel(const char* name, Label* label, bool overwrite)
{
	if (_initialized)
	{
		if (GetSprite(name) == nullptr)
			_labels[name] = label;
		else
		{
			if (overwrite)
				_labels[name] = label;
			else
				LOG_WARNING("Label \"", name, "\" already exists and will not be overwritten");
		}
	}
	else
		LOG_WARNING("Graphics manager was not initialized before adding a label (", name, ")");
}

void GraphicsManager::AddGroup(const char* name, bool overwrite)
{
	if (_initialized)
	{
		if (GetGroup(name) == nullptr)
			_groups[name] = new Group;
		else
		{
			if (overwrite)
				_groups[name] = new Group;
			else
				LOG_WARNING("Group \"", name, "\" already exists and will not be overwritten");
		}
	}
	else
		LOG_WARNING("Graphics manager was not initialized before adding a group (", name, ")");
}

void GraphicsManager::AddMesh(const char* name, Mesh* mesh, bool overwrite)
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
		LOG_WARNING("Graphics manager was not initialized before adding a mesh (", name, ")");
}

Sprite* GraphicsManager::GetSprite(const char* name)
{
	if (_sprites.find(name) != _sprites.end())
		return _sprites[name];

	return nullptr;
}

Label* GraphicsManager::GetLabel(const char* name)
{
	if (_labels.find(name) != _labels.end())
			return _labels[name];

	return nullptr;
}

Group* GraphicsManager::GetGroup(const char* name)
{
	if (_groups.find(name) != _groups.end())
			return _groups[name];
	
	return nullptr;
}

Mesh* GraphicsManager::GetMesh(const char* name)
{
	if (_meshes.find(name) != _meshes.end())
		return _meshes[name];

	return nullptr;
}

void GraphicsManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _groups)
			SafeDelete(item.second);
		for (auto item : _sprites)
			SafeDelete(item.second);
		for (auto item : _labels)
			SafeDelete(item.second);
		for (auto item : _meshes)
			SafeDelete(item.second);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the graphics manager as it was not initialized!");
	}
}