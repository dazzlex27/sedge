/*
===========================================================================
SoundManager.h

Defines a class responsible for managing Sound objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <vector>
#include "CustomTypes.h"

struct gau_Manager;
struct ga_Mixer;

namespace s3dge
{
	class Sound;

	class SoundManager
	{
	private:
		static std::vector<Sound*> _sounds;
		static bool _initialized;

		static gau_Manager* _manager;
		static ga_Mixer* _mixer;

	public:
		static void Initialize(); // must be called upon engine startup
		static void Add(const char* name, const char* path, bool overrideExisting = false);
		static Sound* Get(const char* name);
		static void Update(); // must be called in the engine's main loop
		static void Dispose(); // must be called upon engine shutdown

		static inline uint GetCount() { return _sounds.size(); }

	private:
		SoundManager();
		SoundManager(const SoundManager& tRef) = delete;
		SoundManager& operator = (const SoundManager& tRef) = delete;
		~SoundManager(void) {}

		friend class Sound;
	};
}