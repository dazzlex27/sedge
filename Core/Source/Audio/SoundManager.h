#pragma once

#include <vector>
#include <stdio.h>
#include "Internal/DeleteMacros.h"
#include "Internal/Log.h"
#include "Sound.h"

namespace s3dge
{
	namespace Audio
	{
		class SoundManager
		{
		private:
			static std::vector<Sound*> _sounds;
			static bool _initialized;

			static gau_Manager* _manager;
			static ga_Mixer* _mixer;

		public:
			static void Initialize();
			static void Add(cstring name, cstring path, bool overrideExisting = false);
			static Sound* Get(cstring name);
			static void Update();
			static void Dispose();

			static inline uint GetCount() { return _sounds.size(); }

		private:
			SoundManager();
			SoundManager(const SoundManager& tRef) = delete;
			SoundManager& operator = (const SoundManager& tRef) = delete;
			~SoundManager(void) {}

			friend class Sound;
		};
	}
}