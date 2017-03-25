/*
===========================================================================
Entity.h

Represents a game entity.
===========================================================================
*/

#pragma once

#include "../Components/IComponent.h"
#include "BaseObject.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace s3dge
{
	namespace logic
	{
		class Entity : public BaseObject
		{
		protected:
			math::Matrix4 projection;
			math::Vector3 rotation;
			math::Vector3 scale;
			math::Vector3 position;

		public:
			Entity() { scale = math::Vector3(1, 1, 1); }
			~Entity() {}

		public:
			void AddComponent(IComponent* component)
			{

			}

		private:
			Entity(const Entity& tRef) = delete;				// Disable copy constructor.
			Entity& operator = (const Entity& tRef) = delete;	// Disable assignment operator.
		};
	}
}