#pragma once

#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include <string>
#include "CustomTypes.h"

namespace s3dge
{
	namespace Audio
	{
		class Sound
		{
		private:
			std::string _name;
			std::string _path;
			ga_Sound* _sound;
			ga_Handle* _handle;
			bool _playing;
			int _count;

		public:
			Sound(const std::string& name, const std::string& path);
		public:
			~Sound();

		public:
			void Play();
			void Loop();
			void Stop();
			void Pause();

			inline const std::string& GetName() { return _name; }
			inline bool IsPlaying() { return _playing; }

			friend class SoundManager;
			friend void dispose_sound_callback(ga_Handle * handle, void* context);
			friend void loop_sound_callback(ga_Handle * handle, void* context);
		};
	}
}