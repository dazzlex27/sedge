#pragma once

#include <vector>

namespace s3dge
{
	namespace logic
	{
		class Entity;
	}

	namespace graphics
	{
		class Scene
		{
		private:
			std::vector<logic::Entity*> _entities;
		};
	}
}