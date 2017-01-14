/*
===========================================================================
Entity.h

Takes responsibility for creating Sound objects
===========================================================================
*/

#pragma once

#include "BaseObject.h"
#include "Maths/vec3.h"

namespace s3dge
{
	namespace logic
	{
		class Entity : public BaseObject
		{
		protected:
			maths::vec3f position;

		public:
			virtual void Update() = 0;
			virtual void Draw() = 0;
		};
	}
}