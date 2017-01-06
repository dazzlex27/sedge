/*
===========================================================================
SoundFactory.cpp

Implements SoundFactory class
===========================================================================
*/

#include "SoundFactory.h"
#include "Utilities/FileUtils.h"
#include "Internal/Log.h"

namespace s3dge
{
	namespace Audio
	{
		Sound* SoundFactory::CreateSound(cstring name, cstring path)
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
	}
}
