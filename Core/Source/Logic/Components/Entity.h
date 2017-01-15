/*
===========================================================================
Entity.h

Represents a game entity.
===========================================================================
*/

#pragma once

#include "BaseObject.h"
#include "Maths/Vector3.h"

namespace s3dge
{
	namespace logic
	{
		class Entity : public BaseObject
		{
		protected:
			maths::vec3f translation;
			maths::vec3f rotation;
			maths::vec3f scale;


		public:
			Entity() {}
			~Entity() {}

			virtual void Update() = 0;
			virtual void Render() = 0;
		};
	}
}