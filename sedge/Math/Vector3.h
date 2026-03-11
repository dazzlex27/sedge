/*
===========================================================================
Vector3.h

Implements a 3-component vector class
===========================================================================
*/

#pragma once

namespace sedge
{
	struct Matrix4;

	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3();
		Vector3(const float value);
		Vector3(const float x, const float y, const float z);
		Vector3(const Vector3& other);
		
		const Vector3 operator+(const Vector3& vec) const;
		const Vector3 operator-(const Vector3& vec) const;
		const Vector3 operator*(const Vector3& vec) const;
		const Vector3 operator/(const Vector3& vec) const;

		const Vector3 operator+(float value) const;
		const Vector3 operator-(float value) const;
		const Vector3 operator*(float value) const;
		const Vector3 operator/(float value) const;

		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator*=(const Vector3& other);
		Vector3& operator/=(const Vector3& other);

		Vector3& operator+=(float value);
		Vector3& operator-=(float value);
		Vector3& operator*=(float value);
		Vector3& operator/=(float value);

		friend Vector3 operator+(float value, const Vector3& v);
		friend Vector3 operator-(float value, const Vector3& v);
		friend Vector3 operator*(float value, const Vector3& v);
		friend Vector3 operator/(float value, const Vector3& v);

		friend Vector3 operator*(const Matrix4& m ,const Vector3& v);

		static Vector3 Normalize(const Vector3& vector);
		const float GetDistance(const Vector3& v) const;
		const float GetLength() const;
		static const float GetDotProduct(const Vector3& v1, const Vector3& v2);
		static const Vector3 GetCrossProduct(const Vector3& v1, const Vector3& v2);
	};

	typedef Vector3 vec3;
}
