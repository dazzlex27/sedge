#include "Sound.h"
#include "SoundManager.h"

namespace s3dge
{
	namespace Audio
	{
		Sound::Sound(const std::string& name, const std::string& path)
		{
			_playing = false;
			_count = 0;

			_sound = gau_load_sound_file(path.c_str(), "ogg");
			if (_sound == nullptr)
			{
				LOG_ERROR("Failed to load sound ", name.c_str());
				throw std::exception("Failed to load sound!");
			}
		}

		Sound::~Sound()
		{
			ga_sound_release(_sound);
		}

		void Sound::Play()
		{
			_handle = gau_create_handle_sound(SoundManager::_mixer, _sound, dispose_sound_callback, this, 0);
			ga_handle_play(_handle);

			_count++;
			_playing = true;
		}
		
		void Sound::Loop()
		{
			_handle = gau_create_handle_sound(SoundManager::_mixer, _sound, loop_sound_callback, this, 0);
			ga_handle_play(_handle);

			_playing = true;
		}

		void Sound::Stop()
		{
			if (!_playing)
				return;

			_playing = false;
			ga_handle_stop(_handle);
		}

		void Sound::Pause()
		{
			if (!_playing)
				return;

			_playing = false;
			ga_handle_stop(_handle);
		}

		void dispose_sound_callback(ga_Handle* handle, void* context)
		{
			Sound* sound = (Sound*)context;
			sound->_count--;
			if (!sound->_count)
				sound->Stop();
		}

		void loop_sound_callback(ga_Handle* handle, void* context)
		{
			Sound* sound = (Sound*)context;
			sound->Loop();
			ga_handle_destroy(handle);
		}
	}
}