#include "SoundManager.h"

namespace s3dge
{
	namespace Audio
	{
		std::vector<Sound*> SoundManager::_sounds;
		bool SoundManager::_initialized;

		void SoundManager::Initialize()
		{
			_initialized = true;
		}

		void SoundManager::Add(cstring name, cstring path, bool overrideExisting)
		{
			if (_initialized)
			{
				if (Get(name) != nullptr)
					if (overrideExisting)
					{
						_sounds.push_back(new Sound(name, path));
						return;
					}

				_sounds.push_back(new Sound(name, path));
			}
		}

		Sound* SoundManager::Get(cstring name)
		{
			if (_initialized)
			{
				for (auto item : _sounds)
					if (item->GetName() == name)
						return item;
			}

			return nullptr;
		}

		void SoundManager::Dispose()
		{
			if (_initialized)
			{
				for (auto item : _sounds)
					SafeDelete(item);

				_initialized = false;
			}
		}
	}
}