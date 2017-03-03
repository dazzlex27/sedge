/*
===========================================================================
Point2D.h

Represents a point in two-dimensional coordinate space.
===========================================================================
*/

#pragma once

#include "Math/Vector2.h"

namespace s3dge
{
	namespace graphics
	{
		struct Point2D
		{
			float x;
			float y;

			Point2D(float x, float y) :x(x), y(y){ }
			Point2D(const math::vec2f& vector) : x(vector.x), y(vector.y) { }
			~Point2D() { }
		};
	}
}