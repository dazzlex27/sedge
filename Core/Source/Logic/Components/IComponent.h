#pragma once

namespace s3dge
{
	class GameWorld;

	namespace logic
	{
		class Entity;

		class IComponent
		{
		public:
			virtual void Update(Entity* entity, GameWorld* gameWorld) = 0;
		};
	}
}