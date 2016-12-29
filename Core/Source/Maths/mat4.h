/*
===========================================================================
mat4.h

Declares mat4 class for scene transformations

!!! ATTENTION !!!
THE MAT USES COLUMN-MAJOR ORDER

Example:
Memory layout: 0 1 2 3 4 5 6 7 8 9

Column Major:
0 3 6
1 4 7
2 5 8

Row Major:
0 1 2
3 4 5
6 7 8
===========================================================================
*/

#pragma once

#include "vec3.h"
#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif
#include <math.h>

namespace s3dge
{
	namespace Maths
	{
		struct mat4 // Column-major
		{
			float elements[16];

			mat4();
			mat4(float value);

			mat4 Multiply(const mat4& other);

			mat4 operator*(const mat4& matrix);
			mat4& operator*=(const mat4& other);

			static mat4 GetIdentity();
			static mat4 Translate(const vec3f& vector);
			static mat4 Rotate(const vec3f& vector, float angle);
			static mat4 Scale(const vec3f& vector);

			static mat4 GetOrthographic(float left, float right, float bottom, float top, float near, float far); 
			static mat4 GetPerspective(float fov, float aspectRatio, float near, float far);
		};
	}
}