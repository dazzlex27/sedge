/*
===========================================================================
Renderable2DManager.cpp

Implements the Renderable2DManager class.
===========================================================================
*/

#include "Renderable2DManager.h"
#include "System/Log.h"
#include "System/MemoryManagement.h"

#include "Graphics/Renderables/Sprite.h"
#include "Graphics/Renderables/Label.h"
#include "Graphics/Renderables/Group.h"

using namespace s3dge;
using namespace std;

Renderable2DManager::~Renderable2DManager()
{
	for (auto item : _groups)
		SafeDelete(item.second);
	for (auto item : _sprites)
		SafeDelete(item.second);
	for (auto item : _labels)
		SafeDelete(item.second);
}

void Renderable2DManager::AddSprite(const char* name, Sprite*const sprite, const bool overwrite)
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

void Renderable2DManager::AddLabel(const char* name, Label* label, bool overwrite)
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

void Renderable2DManager::AddGroup(const char* name, bool overwrite)
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

Sprite*const Renderable2DManager::GetSprite(const char* name)
{
	if (_sprites.find(name) != _sprites.end())
		return _sprites[name];

	return nullptr;
}

Label*const Renderable2DManager::GetLabel(const char* name)
{
	if (_labels.find(name) != _labels.end())
			return _labels[name];

	return nullptr;
}

Group*const Renderable2DManager::GetGroup(const char* name)
{
	if (_groups.find(name) != _groups.end())
			return _groups[name];
	
	return nullptr;
}