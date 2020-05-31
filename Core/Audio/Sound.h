/*
===========================================================================
Sound.h

Defines a class responsible for managing audio streams.
At the moment uses Gorilla Audio to do the heavy lifting
===========================================================================
*/

#pragma once

#include <string>
#include <CustomTypes.h>

struct ga_Sound;
struct ga_Handle;

namespace s3dge
{
	class Sound
	{
	private:
		const char* _name;
		const char* _path;
		ga_Sound* _sound;
		ga_Handle* _handle;
		bool _playing;
		bool _created;
		int _count;

	public:
		Sound(const char* name, const char* path);
	public:
		~Sound();

	public:
		void Play();
		void PlayFromStart();
		void Loop();
		void Stop();
		void Pause();

		inline const char* GetName() const { return _name; }
		inline bool IsPlaying() const { return _playing; }

		friend class SoundManager;
		friend void dispose_sound_callback(ga_Handle* handle, void* context);
		friend void loop_sound_callback(ga_Handle* handle, void* context);
	};
}