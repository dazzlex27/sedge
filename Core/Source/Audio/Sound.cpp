/*
===========================================================================
Sound.cpp

Implements Sound class.
===========================================================================
*/

#include "Sound.h"
#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include "SoundManager.h"
#include "System/Log.h"

using namespace s3dge;

Sound::Sound(cstring name, cstring path)
	: _name(name), _path(path), _created(false)
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
	Stop();
	ga_sound_release(_sound);
}

void Sound::Play()
{
	if (!_created)
	{
		PlayFromStart();
		return;
	}

	ga_handle_play(_handle);

	_playing = true;
}

void Sound::PlayFromStart()
{
	_handle = gau_create_handle_sound(SoundManager::_mixer, _sound, dispose_sound_callback, this, 0);
	ga_handle_play(_handle);

	_count++;
	_created = true;
	_playing = true;
}

void Sound::Loop()
{
	_handle = gau_create_handle_sound(SoundManager::_mixer, _sound, loop_sound_callback, this, 0);
	ga_handle_play(_handle);

	_created = true;
	_playing = true;
}

void Sound::Stop()
{
	if (!_playing)
		return;

	_created = false;
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

void s3dge::dispose_sound_callback(ga_Handle* handle, void* context)
{
	Sound* sound = (Sound*)context;
	sound->_count--;
	if (!sound->_count)
		sound->Stop();
}


void s3dge::loop_sound_callback(ga_Handle* handle, void* context)
{
	Sound* sound = (Sound*)context;
	sound->Loop();
	ga_handle_destroy(handle);
}