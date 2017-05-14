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