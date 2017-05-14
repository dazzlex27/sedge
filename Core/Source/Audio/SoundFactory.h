/*
===========================================================================
SoundFactory.h

Takes responsibility for creating Sound objects
===========================================================================
*/

#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	class Sound;

	class SoundFactory
	{
	public:
		static Sound* CreateSound(cstring name, cstring path);

	private:
		SoundFactory();
		SoundFactory(const SoundFactory& tRef) = delete;
		SoundFactory& operator = (const SoundFactory& tRef) = delete;
		~SoundFactory(void) {}
	};
}