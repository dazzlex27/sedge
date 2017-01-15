/*
===========================================================================
Scene.h

A class to represent a game scene (level) which is responsible for managing the entities it contains
(like actors, cameras, items, etc.)
===========================================================================
*/

#pragma once

#include <vector>
#include "Logic/Components/Entity.h"

namespace s3dge
{
	namespace graphics
	{
		class Scene
		{
		private:
			std::vector<logic::Entity*> _entities;

		public:
			Scene();
			~Scene();

			void Update();
			void Render();
		};
	}
}