/*
===========================================================================
SoundManager.cpp

Implements the audio manager class.
===========================================================================
*/

#include "SoundManager.h"
#include "SoundFactory.h"
#include "Internal/Log.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace audio;

std::vector<Sound*> SoundManager::_sounds;
bool SoundManager::_initialized;
ga_Mixer* SoundManager::_mixer;
gau_Manager* SoundManager::_manager;

void SoundManager::Initialize()
{
	if (!_initialized)
	{
		gc_initialize(0);
		_manager = gau_manager_create();
		_mixer = gau_manager_mixer(_manager);
		_initialized = true;
	}
	else
	{
		LOG_WARNING("Sound manager has already been initialized");
	}
}

void SoundManager::Add(cstring name, cstring path, bool overrideExisting)
{
	if (_initialized)
	{
		if (Get(name) != nullptr)
		{
			if (overrideExisting)
			{
				Sound* newSound = SoundFactory::CreateSound(name, path);
				if (newSound != nullptr)
					_sounds.push_back(newSound);
			}
			else
			{
				LOG_WARNING("Sound \"", name, "\" already exists and will not be overwritten");
			}

			return;
		}

		Sound* newSound = SoundFactory::CreateSound(name, path);
		if (newSound != nullptr)
			_sounds.push_back(newSound);
	}
	else
	{
		LOG_WARNING("Sound manager was not initialized before adding a sound file (", name, ")");
	}
}

Sound* SoundManager::Get(cstring name)
{
	if (_initialized)
	{
		for (auto item : _sounds)
			if (strcmp(item->GetName(), name) == 0)
				return item;
	}
	else
	{
		LOG_WARNING("Sound manager was not initialized before getting a sound (", name, ")");
	}

	return nullptr;
}

void SoundManager::Update()
{
	gau_manager_update(_manager);
}

void SoundManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _sounds)
			SafeDelete(item);

		gau_manager_destroy(_manager);
		gc_shutdown();

		_initialized = false;
	}
	else
	{
		LOG_WARNING("Cannot dispose the sound manager as it was not initialized!");
	}
}