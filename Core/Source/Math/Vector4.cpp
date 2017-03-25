/*
===========================================================================
Vector4.cpp

Implements a 4-component vector class
===========================================================================
*/

#include "Vector4.h"
#include <cmath>

using namespace s3dge;
using namespace math;

Vector4::Vector4()
	: x(0), y(0), z(0), w(0) {}

Vector4::Vector4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w) {}

Vector4& Vector4::Add(const Vector4& vector)
{
	this->x += vector.x;
	this->y += vector.y;
	this->z += vector.z;
	this->w += vector.w;

	return *this;
}

Vector4& Vector4::Subtract(const Vector4& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;
	this->z -= vector.z;
	this->w -= vector.w;

	return *this;
}

Vector4& Vector4::Multiply(const Vector4& vector)
{
	this->x *= vector.x;
	this->y *= vector.y;
	this->z *= vector.z;
	this->w *= vector.w;

	return *this;
}

Vector4& Vector4::Multiply(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;

	return *this;
}

Vector4& Vector4::Divide(const Vector4& vector)
{
	this->x /= vector.x;
	this->y /= vector.y;
	this->z /= vector.z;
	this->w /= vector.w;

	return *this;
}

Vector4& Vector4::operator+=(const Vector4& other)
{
	return this->Add(other);
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	return this->Subtract(other);
}

Vector4& Vector4::operator*=(const Vector4& other)
{
	return this->Multiply(other);
}

Vector4& Vector4::operator*=(float value)
{
	return this->Multiply(value);
}

Vector4& Vector4::operator/=(const Vector4& other)
{
	return this->Divide(other);
}

Vector4 Vector4::operator+(const Vector4& v2)
{
	return this->Add(v2);
}

Vector4 Vector4::operator-(const Vector4& v2)
{
	return this->Subtract(v2);
}

Vector4 Vector4::operator*(const Vector4& v2)
{
	return this->Multiply(v2);
}

Vector4 Vector4::operator/(const Vector4& v2)
{
	return this->Divide(v2);
}

Vector4& Vector4::Normalize()
{
	if (GetLength() != 0)
	{
		x /= GetLength();
		y /= GetLength();
		z /= GetLength();
		w /= GetLength();
	}
	
	return *this;
}

float Vector4::GetDistance(Vector4 v) const
{
	Vector4 d(v.x - x, v.y - y, v.z - z, v.w - w);
	return d.GetLength();
}

float Vector4::GetLength() const
{
	return (float)std::sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::GetDotProduct(Vector4 v1, Vector4 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}