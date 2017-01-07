/*
===========================================================================
SoundFactory.h

Takes responsibility for creating Sound objects
===========================================================================
*/

#pragma once

#include "Sound.h"

namespace s3dge
{
	namespace audio
	{
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
}