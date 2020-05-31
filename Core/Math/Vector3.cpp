/*
===========================================================================
Vector3.cpp

Implements a 3-component vector class
===========================================================================
*/

#include "Vector3.h"
#include "Matrix4.h"
#include <cmath>

using namespace sedge;

Vector3::Vector3()
	: x(0), y(0), z(0) 
{
}

Vector3::Vector3(const float value)
	:x(value), y(value), z(value)
{
}

Vector3::Vector3(const float x, const float y, const float z)
	: x(x), y(y), z(z) 
{
}

Vector3::Vector3(const Vector3& vec)
	: x(vec.x), y(vec.y), z(vec.z)
{
}

const Vector3 Vector3::operator+(const Vector3& vec) const
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

const Vector3 Vector3::operator-(const Vector3& vec) const
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

const Vector3 Vector3::operator*(const Vector3& vec) const
{
	return Vector3(x * vec.x, y * vec.y, z * vec.z);
}

const Vector3 Vector3::operator/(const Vector3& vec) const
{
	return Vector3(x / vec.x, y / vec.y, z / vec.z);
}

const Vector3 Vector3::operator+(const float value) const
{
	return Vector3(x + value, y + value, z + value);
}

const Vector3 Vector3::operator-(const float value) const
{
	return Vector3(x - value, y - value, z - value);
}

const Vector3 Vector3::operator*(const float value) const
{
	return Vector3(x * value, y * value, z * value);
}

const Vector3 Vector3::operator/(const float value) const
{
	return Vector3(x / value, y / value, z / value);
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

Vector3& Vector3::operator*=(const Vector3& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;

	return *this;
}

Vector3& Vector3::operator/=(const Vector3& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;

	return *this;
}

Vector3& Vector3::operator+=(const float value)
{
	x += value;
	y += value;
	z += value;

	return *this;
}

Vector3& Vector3::operator-=(const float value)
{
	x -= value;
	y -= value;
	z -= value;

	return *this;
}

Vector3& Vector3::operator*=(const float value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector3& Vector3::operator/=(const float value)
{
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

Vector3 sedge::operator+(float value, const Vector3& v)
{
	return Vector3(v.x + value, v.y + value, v.z + value);
}

Vector3 sedge::operator-(float value, const Vector3& v)
{
	return Vector3(v.x - value, v.y - value, v.z - value);
}

Vector3 sedge::operator*(float value, const Vector3& v)
{
	return Vector3(v.x * value, v.y * value, v.z * value);
}

Vector3 sedge::operator/(float value, const Vector3& v)
{
	return Vector3(v.x / value, v.y / value, v.z / value);
}

Vector3 sedge::operator*(const Matrix4& m, const Vector3& v)
{
	// TODO
	return Vector3();
}

Vector3 Vector3::Normalize(const Vector3& vector)
{
	Vector3 result(vector);

	if (result.GetLength() != 0)
	{
		result.x /= result.GetLength();
		result.y /= result.GetLength();
		result.z /= result.GetLength();
	}

	return result;
}

const float Vector3::GetDistance(const Vector3& v) const
{
	const Vector3 d(v.x - x, v.y - y, v.z - z);
	return d.GetLength();
}

const float Vector3::GetLength() const
{
	return (const float)sqrt(x * x + y * y + z * z);
}

const float Vector3::GetDotProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

const Vector3 Vector3::GetCrossProduct(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}