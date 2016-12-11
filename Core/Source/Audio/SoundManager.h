#pragma once

#include <vector>
#include "Internal/DeleteMacros.h"
#include "Sound.h"

namespace s3dge
{
	namespace Audio
	{
		class SoundManager
		{
		private:
			static std::vector<Sound*> _sounds;

		public:
			static void Initialize();
			static void Add(Sound* texture);
			static void Add(cstring name, cstring path);
			static Sound* Get(cstring name);
			static void Dispose();

			static inline uint GetCount() { return _sounds.size(); }

		private:
			SoundManager();
			SoundManager(const SoundManager& tRef) = delete;
			SoundManager& operator = (const SoundManager& tRef) = delete;
			~SoundManager(void) {}
		};
	}
}