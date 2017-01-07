/*
===========================================================================
Sound.h

Defines a class responsible for managing audio streams.
At the moment uses Gorilla Audio to do the heavy lifting
===========================================================================
*/

#pragma once

#include <string>
#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include "CustomTypes.h"

namespace s3dge
{
	namespace audio
	{
		class Sound
		{
		private:
			cstring _name;
			cstring _path;
			ga_Sound* _sound;
			ga_Handle* _handle;
			bool _playing;
			bool _created;
			int _count;

		public:
			Sound(cstring name, cstring path);
		public:
			~Sound();

		public:
			void Play();
			void PlayFromStart();
			void Loop();
			void Stop();
			void Pause();

			inline cstring GetName() { return _name; }
			inline bool IsPlaying() { return _playing; }

			friend class SoundManager;
			friend void dispose_sound_callback(ga_Handle * handle, void* context);
			friend void loop_sound_callback(ga_Handle * handle, void* context);
		};
	}
}