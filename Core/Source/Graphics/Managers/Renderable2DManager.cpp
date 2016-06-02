/*
===========================================================================
Renderable2DManager.cpp

Implements the Renderable2DManager class.
===========================================================================
*/

#include "Renderable2DManager.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

#include "Graphics/Renderables/Sprite.h"
#include "Graphics/Renderables/Label.h"
#include "Graphics/Renderables/Group.h"

using namespace s3dge;
using namespace std;

map<string, Sprite*> Renderable2DManager::_sprites;
map<string, Label*> Renderable2DManager::_labels;
map<string, Group*> Renderable2DManager::_groups;

bool Renderable2DManager::_initialized;

void Renderable2DManager::Initialize()
{
	if (!_initialized)
	{
		_initialized = true;
	}
	else
	{
		LOG_WARNING("Renderable2D manager has already been initialized");
	}
}

void Renderable2DManager::AddSprite(const char* name, Sprite* sprite, bool overwrite)
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
		LOG_WARNING("Renderable2D manager was not initialized before adding a sprite (", name, ")");
}

void Renderable2DManager::AddLabel(const char* name, Label* label, bool overwrite)
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
		LOG_WARNING("Renderable2D manager was not initialized before adding a label (", name, ")");
}

void Renderable2DManager::AddGroup(const char* name, bool overwrite)
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
		LOG_WARNING("Renderable2D manager was not initialized before adding a group (", name, ")");
}

Sprite* Renderable2DManager::GetSprite(const char* name)
{
	if (_sprites.find(name) != _sprites.end())
		return _sprites[name];

	return nullptr;
}

Label* Renderable2DManager::GetLabel(const char* name)
{
	if (_labels.find(name) != _labels.end())
			return _labels[name];

	return nullptr;
}

Group* Renderable2DManager::GetGroup(const char* name)
{
	if (_groups.find(name) != _groups.end())
			return _groups[name];
	
	return nullptr;
}

void Renderable2DManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _groups)
			SafeDelete(item.second);
		for (auto item : _sprites)
			SafeDelete(item.second);
		for (auto item : _labels)
			SafeDelete(item.second);

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the Renderable2D manager as it was not initialized!");
	}
}