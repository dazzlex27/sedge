/*
===========================================================================
Vector2.h

Defines a 2-component vector class
===========================================================================
*/

#pragma once

namespace s3dge
{
	namespace math
	{
		struct Vector2
		{
			float x;
			float y;
			
			Vector2();
			Vector2(float x, float y);

			Vector2& Add(const Vector2& vector);
			Vector2& Subtract(const Vector2& vector);
			Vector2& Multiply(const Vector2& vector);
			Vector2& Multiply(float value);
			Vector2& Divide(const Vector2& vector);

			Vector2& operator+=(const Vector2& other);
			Vector2& operator-=(const Vector2& other);
			Vector2& operator*=(const Vector2& other);
			Vector2& operator*=(float value);
			Vector2& operator/=(const Vector2& other);
			Vector2 operator+(const Vector2& v2);
			Vector2 operator-(const Vector2& v2);
			Vector2 operator*(const Vector2& v2);
			Vector2 operator/(const Vector2& v2);

			Vector2& Normalize();
			float GetDistance(Vector2 v) const;
			float GetLength() const;

			static float GetDotProduct(Vector2 v1, Vector2 v2);
		};
	}
}