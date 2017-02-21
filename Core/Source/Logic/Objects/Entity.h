/*
===========================================================================
Entity.h

Represents a game entity.
===========================================================================
*/

#pragma once

#include "../Components/IComponent.h"
#include "BaseObject.h"
#include "Math/Vector3.h"

namespace s3dge
{
	namespace logic
	{
		class Entity : public BaseObject
		{
		protected:
			math::mat4 projection;
			math::vec3f rotation;
			math::vec3f scale;
			math::vec3f position;

		public:
			Entity() { scale = math::vec3f(1, 1, 1); }
			~Entity() {}

		public:
			void AddComponent(IComponent* component)
			{

			}

		private:
			Entity(void);
			Entity(const Entity& tRef) = delete;				// Disable copy constructor.
			Entity& operator = (const Entity& tRef) = delete;	// Disable assignment operator.
			~Entity(void) = delete;
		};
	}
}