/*
===========================================================================
SoundFactory.cpp

Implements SoundFactory class
===========================================================================
*/

#include "SoundFactory.h"
#include "Sound.h"
#include "System/FileUtils.h"
#include "System/Logger.h"

using namespace sedge;

Sound* SoundFactory::CreateSound(const char* name, const char* path)
{
	if (strcmp(name, "") == 0)
	{
		LOG_ERROR("Cannot create a sound with an empty name string");
		return nullptr;
	}

	if (strcmp(path, "") == 0)
	{
		LOG_ERROR("Cannot create a sound with an empty path string");
		return nullptr;
	}

	if (!FileUtils::CheckFileExists(path))
	{
		LOG_ERROR("Sound file ", "\"name\"", " was not found");
		return nullptr;
	}

	return new Sound(name, path);
}