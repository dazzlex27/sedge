/*
===========================================================================
GraphicsComponent.h

Defines a component for handling visual representation of entities.
Designed to fit component-based entity model.
Should be composed by the entity in question to be enable that entity to be displayed on screen.
===========================================================================
*/

#pragma once

#include "IComponent.h"
#include "Logic/Objects/Entity.h"

namespace s3dge
{
	namespace logic
	{
		class GraphicsComponent : IComponent
		{
		public:
			virtual void Update(Entity* entity, GameWorld* gameWorld) override;
			virtual ~GraphicsComponent() { }
		};
	}
}