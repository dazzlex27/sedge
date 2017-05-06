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

Vector2::Vector2(float x, float y)
	: x(x), y(y) 
{
}

Vector2& Vector2::Add(const Vector2& vector)
{
	this->x += vector.x;
	this->y += vector.y;

	return *this;
}

Vector2& Vector2::Subtract(const Vector2& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;

	return *this;
}

Vector2& Vector2::Multiply(const Vector2& vector)
{
	this->x *= vector.x;
	this->y *= vector.y;

	return *this;
}

Vector2& Vector2::Multiply(float value)
{
	this->x *= value;
	this->y *= value;

	return *this;
}

Vector2& Vector2::Divide(const Vector2& vector)
{
	this->x /= vector.x;
	this->y /= vector.y;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	return this->Add(other);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	return this->Subtract(other);
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	return this->Multiply(other);
}

Vector2& Vector2::operator*=(float value)
{
	return this->Multiply(value);
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	return this->Divide(other);
}

Vector2 Vector2::operator+(const Vector2& v2)
{
	return this->Add(v2);
}

Vector2 Vector2::operator-(const Vector2& v2)
{
	return this->Subtract(v2);
}

Vector2 Vector2::operator*(const Vector2& v2)
{
	return this->Multiply(v2);
}

Vector2 Vector2::operator/(const Vector2& v2)
{
	return this->Divide(v2);
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

float Vector2::GetDistance(Vector2 v) const
{
	Vector2 d(v.x - x, v.y - y);
	return d.GetLength();
}

float Vector2::GetLength() const
{
	return (float)std::sqrt(x * x + y * y);
}

float Vector2::GetDotProduct(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}