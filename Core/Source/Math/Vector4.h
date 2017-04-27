/*
===========================================================================
Vector4.h

Implements a 4-component vector class
===========================================================================
*/

#pragma once

namespace s3dge
{
	namespace math
	{
		struct Vector4
		{
			float x;
			float y;
			float z;
			float w;

			Vector4();
			Vector4(float x, float y, float z, float w);

			Vector4& Add(const Vector4& vector);
			Vector4& Subtract(const Vector4& vector);
			Vector4& Multiply(const Vector4& vector);
			Vector4& Multiply(float value);
			Vector4& Divide(const Vector4& vector);

			Vector4& operator+=(const Vector4& other);
			Vector4& operator-=(const Vector4& other);
			Vector4& operator*=(const Vector4& other);
			Vector4& operator*=(float value);
			Vector4& operator/=(const Vector4& other);
			Vector4 operator+(const Vector4& v2);
			Vector4 operator-(const Vector4& v2);
			Vector4 operator*(const Vector4& v2);
			Vector4 operator/(const Vector4& v2);

			Vector4& Normalize();
			float GetDistance(Vector4 v) const;
			float GetLength() const;
			
			static float GetDotProduct(Vector4 v1, Vector4 v2);
		};
	}
}