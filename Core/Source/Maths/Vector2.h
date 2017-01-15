/*
===========================================================================
Vector2.h

Implements a 2-component vector class
===========================================================================
*/

#pragma once

namespace s3dge
{
	namespace maths
	{
		template <typename T>
		struct Vector2
		{
			T x;
			T y;
			
			Vector2()
				: x(0), y(0) {}

			Vector2(T x, T y)
				: x(x), y(y) {}

			Vector2& Add(const Vector2& vector)
			{
				this->x += vector.x;
				this->y += vector.y;

				return *this;
			}

			Vector2& Subtract(const Vector2& vector)
			{
				this->x -= vector.x;
				this->y -= vector.y;

				return *this;
			}

			Vector2& Multiply(const Vector2& vector)
			{
				this->x *= vector.x;
				this->y *= vector.y;

				return *this;
			}

			Vector2& Divide(const Vector2& vector)
			{
				this->x /= vector.x;
				this->y /= vector.y;

				return *this;
			}

			Vector2& operator+=(const Vector2& other)
			{
				return this->Add(other);
			}

			Vector2& operator-=(const Vector2& other)
			{
				return this->Subtract(other);
			}

			Vector2& operator*=(const Vector2& other)
			{
				return this->Multiply(other);
			}

			Vector2& operator/=(const Vector2& other)
			{
				return this->Divide(other);
			}

			Vector2 operator+(const Vector2& v2)
			{
				return this->Add(v2);
			}

			Vector2 operator-(const Vector2& v2)
			{
				return this->Subtract(v2);
			}

			Vector2 operator*(const Vector2& v2)
			{
				return this->Multiply(v2);
			}

			Vector2 operator/(const Vector2& v2)
			{
				return this->Divide(v2);
			}

			Vector2& Normalize() {
				if (length() == 0) return *this;
				*this *= (1.0 / length());
				return *this;
			}

			float GetDistance(Vector2 v) const {
				vec2 d(v.x - x, v.y - y);
				return d.length();
			}

			float GetLength() const {
				return std::sqrt(x * x + y * y);
			}

			static float GetDot(Vector2 v1, Vector2 v2) {
				return v1.x * v2.x + v1.y * v2.y;
			}
			static float GetCross(Vector2 v1, Vector2 v2) {
				return (v1.x * v2.y) - (v1.y * v2.x);
			}
		};

		typedef Vector2<float> vec2f;
		typedef Vector2<double> vec2d;
	}
}