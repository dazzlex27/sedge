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
			math::vec3f position;

		public:
			Entity() {}
			~Entity() {}
		};
	}
}