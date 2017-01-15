/*
===========================================================================
Entity.h

Represents a game entity.
===========================================================================
*/

#pragma once

#include "BaseObject.h"
#include "Math/Vector3.h"

namespace s3dge
{
	namespace logic
	{
		class Entity : public BaseObject
		{
		protected:
			math::vec3f translation;
			math::vec3f rotation;
			math::vec3f scale;

		public:
			Entity() {}
			~Entity() {}

			virtual void Update() = 0;
			virtual void Render() = 0;
		};
	}
}