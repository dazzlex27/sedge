/*
===========================================================================
Vector2.h

Defines a 2-component vector class
===========================================================================
*/

#pragma once

namespace sedge
{
	struct Vector2
	{
		float x;
		float y;

		Vector2();
		Vector2(const float x, const float y);

		Vector2& Add(const Vector2& vector);
		Vector2& Subtract(const Vector2& vector);
		Vector2& Multiply(const Vector2& vector);
		Vector2& Multiply(const float value);
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
		const float GetDistance(const Vector2& v) const;
		const float GetLength() const;

		static const float GetDotProduct(const Vector2& v1, const Vector2& v2);
	};
}