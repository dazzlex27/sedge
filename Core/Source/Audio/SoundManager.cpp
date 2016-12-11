#include "SoundManager.h"

namespace s3dge
{
	namespace Audio
	{
		std::vector<Sound*> SoundManager::_sounds;

		void SoundManager::Initialize()
		{

		}

		void SoundManager::Add(Sound* texture)
		{
			_sounds.push_back(texture);
		}

		void SoundManager::Add(cstring name, cstring path)
		{
			_sounds.push_back(new Sound(name, path));
		}

		Sound* SoundManager::Get(cstring name)
		{
			for (auto item : _sounds)
				if (item->GetName() == name)
					return item;

			return nullptr;
		}

		void SoundManager::Dispose()
		{
			for (auto item : _sounds)
				SafeDelete(item);
		}
	}
}