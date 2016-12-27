#include "SoundManager.h"

namespace s3dge
{
	namespace Audio
	{
		std::vector<Sound*> SoundManager::_sounds;
		bool SoundManager::_initialized;
		ga_Mixer* SoundManager::_mixer;
		gau_Manager* SoundManager::_manager;

		void SoundManager::Initialize()
		{
			if (!_initialized)
			{
				gc_initialize(0);
				_manager = gau_manager_create();
				_mixer = gau_manager_mixer(_manager);
				_initialized = true;
			}
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
					else
					{
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

		void SoundManager::Update()
		{
			gau_manager_update(_manager);
		}

		void SoundManager::Dispose()
		{
			if (_initialized)
			{
				for (auto item : _sounds)
					SafeDelete(item);

				gau_manager_destroy(_manager);
				gc_shutdown();

				_initialized = false;
			}
		}
	}
}