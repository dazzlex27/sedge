#pragma once

namespace S3DGE
{
	namespace Maths
	{
		template <typename T>
		struct vec4
		{
			T x;
			T y;
			T z;
			T w;

			vec4()
				: x(0), y(0), z(0), w(0) {}

			vec4(T x, T y, T z, T w)
				: x(x), y(y), z(z), w(w) {}

			vec4& Add(const vec4& vector)
			{
				this->x += vector.x;
				this->y += vector.y;
				this->z += vector.z;
				this->w += vector.w;

				return *this;
			}

			vec4& Subtract(const vec4& vector)
			{
				this->x -= vector.x;
				this->y -= vector.y;
				this->z -= vector.z;
				this->w -= vector.w;

				return *this;
			}

			vec4& Multiply(const vec4& vector)
			{
				this->x *= vector.x;
				this->y *= vector.y;
				this->z *= vector.z;
				this->w *= vector.w;

				return *this;
			}

			vec4& Divide(const vec4& vector)
			{
				this->x /= vector.x;
				this->y /= vector.y;
				this->z /= vector.z;
				this->w /= vector.w;

				return *this;
			}

			vec4& operator+=(const vec4& other)
			{
				return this->Add(other);
			}

			vec4& operator-=(const vec4& other)
			{
				return this->Subtract(other);
			}

			vec4& operator*=(const vec4& other)
			{
				return this->Multiply(other);
			}

			vec4& operator/=(const vec4& other)
			{
				return this->Divide(other);
			}

			vec4 operator+(const vec4& v2)
			{
				return this->Add(v2);
			}

			vec4 operator-(const vec4& v2)
			{
				return this->Subtract(v2);
			}

			vec4 operator*(const vec4& v2)
			{
				return this->Multiply(v2);
			}

			vec4 operator/(const vec4& v2)
			{
				return this->Divide(v2);
			}
		};

		typedef vec4<float> vec4f;
		typedef vec4<double> vec4d;
	}
}