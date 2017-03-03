/*
===========================================================================
Point3D.h

Represents a point in three-dimensional coordinate space.
===========================================================================
*/

#pragma once

#include "Math/Vector3.h"

namespace s3dge
{
	namespace graphics
	{
		struct Point3D
		{
			float x;
			float y;
			float z;

			Point3D(float x, float y, float z) :x(x), y(y), z(z) { }
			Point3D(const math::vec3f& vector) : x(vector.x), y(vector.y), z(vector.z) { }
			~Point3D() { }
		};
	}
}