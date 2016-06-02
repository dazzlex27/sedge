/*
===========================================================================
Vector2.cpp

Implements a 2-component vector class
===========================================================================
*/

#include "Vector2.h"
#include <cmath>

using namespace s3dge;

Vector2::Vector2()
	: x(0), y(0) 
{
}

Vector2::Vector2(const float x, const float y)
	: x(x), y(y) 
{
}

Vector2& Vector2::Add(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector2& Vector2::Subtract(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Vector2& Vector2::Multiply(const Vector2& vector)
{
	x *= vector.x;
	y *= vector.y;

	return *this;
}

Vector2& Vector2::Multiply(const float value)
{
	x *= value;
	y *= value;

	return *this;
}

Vector2& Vector2::Divide(const Vector2& vector)
{
	x /= vector.x;
	y /= vector.y;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	return Add(other);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	return Subtract(other);
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	return Multiply(other);
}

Vector2& Vector2::operator*=(float value)
{
	return Multiply(value);
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	return Divide(other);
}

Vector2 Vector2::operator+(const Vector2& v2)
{
	return Add(v2);
}

Vector2 Vector2::operator-(const Vector2& v2)
{
	return Subtract(v2);
}

Vector2 Vector2::operator*(const Vector2& v2)
{
	return Multiply(v2);
}

Vector2 Vector2::operator/(const Vector2& v2)
{
	return Divide(v2);
}

Vector2& Vector2::Normalize()
{
	if (GetLength() != 0)
	{
		x /= GetLength();
		y /= GetLength();
	}

	return *this;
}

const float Vector2::GetDistance(const Vector2& v) const
{
	const Vector2 d(v.x - x, v.y - y);
	return d.GetLength();
}

const float Vector2::GetLength() const
{
	return (float)std::sqrt(x * x + y * y);
}

const float Vector2::GetDotProduct(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}