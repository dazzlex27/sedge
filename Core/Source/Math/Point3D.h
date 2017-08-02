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
	struct Point3D
	{
		float x;
		float y;
		float z;

		Point3D() : x(0), y(0), z(0) { }
		Point3D(const float x, const float y, const float z) :x(x), y(y), z(z) { }
		Point3D(const Vector3& vector) : x(vector.x), y(vector.y), z(vector.z) { }
		~Point3D() { }
	};
}