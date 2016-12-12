#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	namespace Audio
	{
		class Sound
		{
		private:
			cstring _name;
			cstring _path;

		private:
			Sound(cstring name, cstring path);
		public:
			~Sound();

		public:
			void Play();
			void Stop();
			void Pause();

			inline cstring GetName() { return _name; }

			friend class SoundManager;
		};
	}
}