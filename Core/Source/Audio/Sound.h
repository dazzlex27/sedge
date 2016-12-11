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

		public:
			Sound(cstring name, cstring path);
			~Sound();

		public:
			void Play();
			void Stop();
			void Pause();

			inline cstring GetName() { return _name; }
		};
	}
}