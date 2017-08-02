/*
===========================================================================
Vector4.cpp

Implements a 4-component vector class
===========================================================================
*/

#include "Vector4.h"
#include <cmath>

using namespace s3dge;

Vector4::Vector4()
	: x(0), y(0), z(0), w(0) {}

Vector4::Vector4(const float x, const float y, const float z, const float w)
	: x(x), y(y), z(z), w(w) {}

Vector4& Vector4::Add(const Vector4& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;

	return *this;
}

Vector4& Vector4::Subtract(const Vector4& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;

	return *this;
}

Vector4& Vector4::Multiply(const Vector4& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;

	return *this;
}

Vector4& Vector4::Multiply(const float value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;

	return *this;
}

Vector4& Vector4::Divide(const Vector4& vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;

	return *this;
}

Vector4& Vector4::operator+=(const Vector4& other)
{
	return Add(other);
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	return Subtract(other);
}

Vector4& Vector4::operator*=(const Vector4& other)
{
	return Multiply(other);
}

Vector4& Vector4::operator*=(float value)
{
	return Multiply(value);
}

Vector4& Vector4::operator/=(const Vector4& other)
{
	return Divide(other);
}

Vector4 Vector4::operator+(const Vector4& v2)
{
	return Add(v2);
}

Vector4 Vector4::operator-(const Vector4& v2)
{
	return Subtract(v2);
}

Vector4 Vector4::operator*(const Vector4& v2)
{
	return Multiply(v2);
}

Vector4 Vector4::operator/(const Vector4& v2)
{
	return Divide(v2);
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

const float Vector4::GetDistance(const Vector4& v) const
{
	const Vector4 d(v.x - x, v.y - y, v.z - z, v.w - w);
	return d.GetLength();
}

const float Vector4::GetLength() const
{
	return (const float)std::sqrt(x * x + y * y + z * z + w * w);
}

const float Vector4::GetDotProduct(const Vector4& v1, const Vector4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}