/*
===========================================================================
Vector3.cpp

Implements a 3-component vector class
===========================================================================
*/

#include "Vector3.h"
#include "Math/Point3D.h"
#include "Matrix4.h"
#include <cmath>

using namespace s3dge;

Vector3::Vector3()
	: x(0), y(0), z(0) 
{
}

Vector3::Vector3(const Point3D& point)
	: x(point.x), y(point.y), z(point.z)
{
}

Vector3::Vector3(const float x, const float y, const float z)
	: x(x), y(y), z(z) 
{
}

Vector3::Vector3(const Vector3& other)
	: x(other.x), y(other.y), z(other.z)
{
}

Vector3& Vector3::Add(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

Vector3& Vector3::Subtract(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

Vector3& Vector3::Multiply(const Vector3& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;

	return *this;
}

Vector3& Vector3::Multiply(const float value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector3& Vector3::Divide(const Vector3& vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;

	return *this;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	return Add(other);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	return Subtract(other);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	return Multiply(other);
}

Vector3& Vector3::operator*=(const float value)
{
	return Multiply(value);
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	return Divide(other);
}

Vector3 s3dge::operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 s3dge::operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 s3dge::operator*(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3 s3dge::operator/(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vector3 s3dge::operator+(const Vector3& v, float value)
{
	return Vector3(v.x + value, v.y + value, v.z + value);
}

Vector3 s3dge::operator-(const Vector3& v, float value)
{
	return Vector3(v.x - value, v.y - value, v.z - value);
}

Vector3 s3dge::operator*(const Vector3& v, float value)
{
	return Vector3(v.x * value, v.y * value, v.z * value);
}

Vector3 s3dge::operator/(const Vector3& v, float value)
{
	return Vector3(v.x / value, v.y / value, v.z / value);
}

Vector3 s3dge::operator+(float value, const Vector3& v)
{
	return Vector3(v.x + value, v.y + value, v.z + value);
}

Vector3 s3dge::operator-(float value, const Vector3& v)
{
	return Vector3(v.x - value, v.y - value, v.z - value);
}

Vector3 s3dge::operator*(float value, const Vector3& v)
{
	return Vector3(v.x * value, v.y * value, v.z * value);
}

Vector3 s3dge::operator/(float value, const Vector3& v)
{
	return Vector3(v.x / value, v.y / value, v.z / value);
}

Vector3 s3dge::operator*(const Matrix4& m, const Vector3& v)
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
	return (const float)std::sqrt(x * x + y * y + z * z);
}

const float Vector3::GetDotProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

const Vector3 Vector3::GetCrossProduct(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}