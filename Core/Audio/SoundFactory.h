/*
===========================================================================
SoundFactory.h

Takes responsibility for creating Sound objects
===========================================================================
*/

#pragma once

#include <CustomTypes.h>

namespace sedge
{
	class Sound;

	class SoundFactory
	{
	public:
		static Sound* CreateSound(const char* name, const char* path);

	private:
		SoundFactory();
		SoundFactory(const SoundFactory& tRef) = delete;
		SoundFactory& operator = (const SoundFactory& tRef) = delete;
		~SoundFactory(void) {}
	};
}