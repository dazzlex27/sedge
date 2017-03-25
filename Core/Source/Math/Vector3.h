/*
===========================================================================
Vector3.h

Implements a 3-component vector class
===========================================================================
*/

#pragma once

namespace s3dge
{
	namespace math
	{
		struct Vector3
		{
			float x;
			float y;
			float z;

			Vector3();
			Vector3(float x, float y, float z);
			Vector3(const Vector3& other);

			Vector3& Add(const Vector3& vector);
			Vector3& Subtract(const Vector3& vector);
			Vector3& Multiply(const Vector3& vector);
			Vector3& Multiply(float value);
			Vector3& Divide(const Vector3& vector);
			
			Vector3& operator+=(const Vector3& other);
			Vector3& operator-=(const Vector3& other);
			Vector3& operator*=(const Vector3& other);
			Vector3& operator*=(float value);
			Vector3& operator/=(const Vector3& other);
			Vector3 operator+(const Vector3& v2);
			Vector3 operator-(const Vector3& v2);
			Vector3 operator*(const Vector3& v2);
			Vector3 operator/(const Vector3& v2);

			friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
			friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
			friend Vector3 operator*(const Vector3& v1, const Vector3& v2);
			friend Vector3 operator/(const Vector3& v1, const Vector3& v2);

			Vector3& Normalize();
			float GetDistance(const Vector3& v) const;
			float GetLength() const;
			static float GetDotProduct(const Vector3& v1, const Vector3& v2);
			static Vector3 GetCrossProduct(const Vector3& v1, const Vector3& v2);
		};
	}
}
