#pragma once

namespace S3DGE
{
	namespace Maths
	{
		template <typename T>
		struct vec2
		{
			T x;
			T y;
			
			vec2()
				: x(0), y(0) {}

			vec2(T x, T y)
				: x(x), y(y) {}

			vec2& Add(const vec2& vector)
			{
				this->x += vector.x;
				this->y += vector.y;

				return *this;
			}

			vec2& Subtract(const vec2& vector)
			{
				this->x -= vector.x;
				this->y -= vector.y;

				return *this;
			}

			vec2& Multiply(const vec2& vector)
			{
				this->x *= vector.x;
				this->y *= vector.y;

				return *this;
			}

			vec2& Divide(const vec2& vector)
			{
				this->x /= vector.x;
				this->y /= vector.y;

				return *this;
			}

			vec2& operator+=(const vec2& other)
			{
				return this->Add(other);
			}

			vec2& operator-=(const vec2& other)
			{
				return this->Subtract(other);
			}

			vec2& operator*=(const vec2& other)
			{
				return this->Multiply(other);
			}

			vec2& operator/=(const vec2& other)
			{
				return this->Divide(other);
			}

			vec2 operator+(const vec2& v2)
			{
				return this->Add(v2);
			}

			vec2 operator-(const vec2& v2)
			{
				return this->Subtract(v2);
			}

			vec2 operator*(const vec2& v2)
			{
				return this->Multiply(v2);
			}

			vec2 operator/(const vec2& v2)
			{
				return this->Divide(v2);
			}

			vec2& Normalize() {
				if (length() == 0) return *this;
				*this *= (1.0 / length());
				return *this;
			}

			float GetDistance(vec2 v) const {
				vec2 d(v.x - x, v.y - y);
				return d.length();
			}

			float GetLength() const {
				return std::sqrt(x * x + y * y);
			}

			static float GetDot(vec2 v1, vec2 v2) {
				return v1.x * v2.x + v1.y * v2.y;
			}
			static float GetCross(vec2 v1, vec2 v2) {
				return (v1.x * v2.y) - (v1.y * v2.x);
			}
		};

		typedef vec2<float> vec2f;
		typedef vec2<double> vec2d;
	}
}