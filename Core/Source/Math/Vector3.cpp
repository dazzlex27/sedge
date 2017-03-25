/*
===========================================================================
Vector3.cpp

Implements a 3-component vector class
===========================================================================
*/

#include "Vector3.h"
#include <cmath>

using namespace s3dge;
using namespace math;

Vector3::Vector3()
	: x(0), y(0), z(0) 
{
}

Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z) 
{
}

Vector3::Vector3(const Vector3& other)
	: x(other.x), y(other.y), z(other.z)
{
}

Vector3& Vector3::Add(const Vector3& vector)
{
	this->x += vector.x;
	this->y += vector.y;
	this->z += vector.z;

	return *this;
}

Vector3& Vector3::Subtract(const Vector3& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;
	this->z -= vector.z;

	return *this;
}

Vector3& Vector3::Multiply(const Vector3& vector)
{
	this->x *= vector.x;
	this->y *= vector.y;
	this->z *= vector.z;

	return *this;
}

Vector3& Vector3::Multiply(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;

	return *this;
}

Vector3& Vector3::Divide(const Vector3& vector)
{
	this->x /= vector.x;
	this->y /= vector.y;
	this->z /= vector.z;

	return *this;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	return this->Add(other);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	return this->Subtract(other);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	return this->Multiply(other);
}

Vector3& Vector3::operator*=(float value)
{
	return this->Multiply(value);
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	return this->Divide(other);
}

Vector3 Vector3::operator+(const Vector3& v2)
{
	return this->Add(v2);
}

Vector3 Vector3::operator-(const Vector3& v2)
{
	return this->Subtract(v2);
}

Vector3 Vector3::operator*(const Vector3& v2)
{
	return this->Multiply(v2);
}

Vector3 Vector3::operator/(const Vector3& v2)
{
	return this->Divide(v2);
}

Vector3 s3dge::math::operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 s3dge::math::operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 s3dge::math::operator*(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3 s3dge::math::operator/(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vector3& Vector3::Normalize()
{
	if (GetLength() != 0)
	{
		x /= GetLength();
		y /= GetLength();
		z /= GetLength();
	}

	return *this;
}

float Vector3::GetDistance(const Vector3& v) const
{
	Vector3 d(v.x - x, v.y - y, v.z - z);
	return d.GetLength();
}

float Vector3::GetLength() const
{
	return (float)std::sqrt(x * x + y * y + z * z);
}

float Vector3::GetDotProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::GetCrossProduct(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}