/*
===========================================================================
PhysicsComponent.h

Defines a component for handling collision of entities.
Designed to fit component-based entity model.
Should be composed by the entity in question to be enable that entity to interact with the game world.
===========================================================================
*/

#pragma once

#include "IComponent.h"
#include "Logic/Objects/Entity.h"

namespace s3dge
{
	namespace logic
	{
		class PhysicsComponent : IComponent
		{
		public:
			virtual void Update(Entity* entity, GameWorld* gameWorld) override;
			virtual ~PhysicsComponent() { }
		};
	}
}