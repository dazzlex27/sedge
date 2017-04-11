#pragma once

namespace s3dge
{
	class GameWorld;

	class Entity;

	class IComponent
	{
	public:
		virtual void Update(Entity* entity, GameWorld* gameWorld) = 0;
	};
}
