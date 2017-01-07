/*
===========================================================================
Sound.cpp

Implements Sound class.
===========================================================================
*/

#include "Sound.h"
#include "SoundManager.h"
#include "Internal/Log.h"

using namespace s3dge;
using namespace audio;

Sound::Sound(cstring name, cstring path)
	: _name(name), _path(path)
{
	_playing = false;
	_count = 0;

	_sound = gau_load_sound_file(path, "ogg");
	if (_sound == nullptr)
	{
		LOG_ERROR("Failed to load sound ", name);
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

void s3dge::audio::dispose_sound_callback(ga_Handle* handle, void* context)
{
	Sound* sound = (Sound*)context;
	sound->_count--;
	if (!sound->_count)
		sound->Stop();
}


void s3dge::audio::loop_sound_callback(ga_Handle* handle, void* context)
{
	Sound* sound = (Sound*)context;
	sound->Loop();
	ga_handle_destroy(handle);
}