/*
===========================================================================
GraphicsManager.cpp

Implements the renderables manager class.
===========================================================================
*/

#include "GraphicsManager.h"
#include "Internal/Log.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace graphics;
using namespace std;

map<cstring, Sprite*> GraphicsManager::_sprites;
map<cstring, Label*> GraphicsManager::_labels;
map<cstring, Group*> GraphicsManager::_groups;
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

void GraphicsManager::AddSprite(cstring name, float x, float y, float w, float h, uint c, Texture2D* t, bool overrideExisting)
{
	if (_initialized)
	{
		if (GetSprite(name) != nullptr)
		{
			if (overrideExisting)
			{
				Sprite* newSprite;

				if (t == nullptr)
					newSprite = new Sprite(x, y, w, h, c);
				else
					newSprite = new Sprite(x, y, w, h, t);

				_sprites[name] = newSprite;
			}
			else
			{
				LOG_WARNING("Sprite \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Sprite* newSprite;

		if (t == nullptr)
			newSprite = new Sprite(x, y, w, h, c);
		else
			newSprite = new Sprite(x, y, w, h, t);

		_sprites[name] = newSprite;
	}
	else
	{
		LOG_WARNING("Graphics manager was not initialized before adding a sprite (", name, ")");
	}
}

void GraphicsManager::AddLabel(cstring name, const string& text, Font* font, float x, float y, float w, float h, uint c, bool overrideExisting)
{
	if (_initialized)
	{
		if (GetLabel(name) != nullptr)
		{
			if (overrideExisting)
			{
				_labels[name] = new Label(text, font, x, y, w, h, c);
			}
			else
			{
				LOG_WARNING("Label \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		_labels[name] = new Label(text, font, x, y, w, h, c);
	}
	else
	{
		LOG_WARNING("Graphics manager was not initialized before adding a label (", name, ")");
	}
}

void GraphicsManager::AddGroup(cstring name, bool overrideExisting)
{
	if (_initialized)
	{
		if (GetGroup(name) != nullptr)
		{
			if (overrideExisting)
			{
				_groups[name] = new Group();
			}
			else
			{
				LOG_WARNING("Group \"", name, "\" already exists and will not be overwritten");
			}
		}

		_groups[name] = new Group();
	}
	else
	{
		LOG_WARNING("Graphics manager was not initialized before adding a group (", name, ")");
	}
}

Sprite* GraphicsManager::GetSprite(cstring name)
{
	if (_sprites.find(name) != _sprites.end())
		return _sprites[name];

	return nullptr;
}

Label* GraphicsManager::GetLabel(cstring name)
{
	if (_labels.find(name) != _labels.end())
			return _labels[name];

	return nullptr;
}

Group* GraphicsManager::GetGroup(cstring name)
{
	if (_groups.find(name) != _groups.end())
			return _groups[name];
	
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

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the graphics manager as it was not initialized!");
	}
}