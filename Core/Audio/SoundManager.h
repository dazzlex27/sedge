/*
===========================================================================
SoundManager.h

Defines a class responsible for managing Sound objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <vector>
#include <CustomTypes.h>

struct gau_Manager;
struct ga_Mixer;

namespace s3dge
{
	class Sound;

	class SoundManager
	{
	private:
		std::vector<Sound*> _sounds;

		gau_Manager* _manager;
		static ga_Mixer* _mixer;

	public:
		void AddSound(const char*const name, const char*const path, const bool overrideExisting = false);
		Sound*const GetSound(const char*const name);
		void Update(); // must be called in the engine's main loop

		inline uint GetCount() { return _sounds.size(); }
		
		~SoundManager();

	private:
		SoundManager();
		SoundManager(const SoundManager& tRef) = delete;
		SoundManager& operator = (const SoundManager& tRef) = delete;

		friend class Sound;
		friend class Window;
	};
}