/*
===========================================================================
SoundManager.cpp

Implements the audio manager class.
===========================================================================
*/

#include "SoundManager.h"
#include "SoundFactory.h"
#include "Sound.h"
#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include "System/Log.h"
#include "System/MemoryManagement.h"

using namespace s3dge;

ga_Mixer* SoundManager::_mixer;

SoundManager::SoundManager()
{
	gc_initialize(0);
	_manager = gau_manager_create();
	_mixer = gau_manager_mixer(_manager);
}

void SoundManager::AddSound(const char* name, const char* path, bool overrideExisting)
{
	if (GetSound(name) != nullptr)
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
	}
	else
	{
		Sound* newSound = SoundFactory::CreateSound(name, path);
		if (newSound != nullptr)
			_sounds.push_back(newSound);
	}
}

Sound*const SoundManager::GetSound(const char* name)
{
	for (auto item : _sounds)
		if (strcmp(item->GetName(), name) == 0)
			return item;

	LOG_ERROR("Sound named \"", name, "\" was not found!");
	return nullptr;
}

void SoundManager::Update()
{
	gau_manager_update(_manager);
}

SoundManager::~SoundManager()
{
	for (auto item : _sounds)
		SafeDelete(item);

	gau_manager_destroy(_manager);
	gc_shutdown();
}