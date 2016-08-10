#pragma once

#include "vec3.h"
#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif
#include <math.h>

namespace S3DGE
{
	namespace Maths
	{
		struct mat4 // Column-major
		{
			float elements[16];

			mat4();
			mat4(float value);

			mat4& Multiply(const mat4& other);

			mat4 operator*(const mat4& matrix);
			mat4& operator*=(const mat4& other);

			static mat4 GetIdentity();
			static mat4 Translate(const vec3f& vector);
			static mat4 Rotate(const vec3f& vector, double angle);
			static mat4 Scale(const vec3f& vector);

			static mat4 GetOrthographic(float left, float right, float top, float bottom, float near, float far); 
			static mat4 GetPerspective(float fov, float aspectRatio, float near, float far);
		};
	}
}