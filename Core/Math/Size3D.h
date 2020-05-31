/*
===========================================================================
Size3D.h

Represents a three-dimensional size.
===========================================================================
*/

#pragma once

#include "Math/Vector3.h"

namespace sedge
{
	struct Size3D
	{
		float width;
		float height;
		float depth;

		Size3D(const float width, const float height, const float depth)
			: width(width), height(height), depth(depth) { }
		Size3D(const Vector3& vector)
			: width(vector.x), height(vector.y), depth(vector.z) { }
	};
}