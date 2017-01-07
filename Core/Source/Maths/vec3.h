/*
===========================================================================
vec3.h

Implements a 3-component vector class
===========================================================================
*/

#pragma once

namespace s3dge
{
	namespace maths
	{
		template <typename T>
		struct vec3
		{
			T x;
			T y;
			T z;

			vec3()
				: x(0), y(0), z(0) {}

			vec3(T x, T y, T z)
				: x(x), y(y), z(z) {}

			vec3& Add(const vec3& vector)
			{
				this->x += vector.x;
				this->y += vector.y;
				this->z += vector.z;

				return *this;
			}

			vec3& Subtract(const vec3& vector)
			{
				this->x -= vector.x;
				this->y -= vector.y;
				this->z -= vector.z;

				return *this;
			}

			vec3& Multiply(const vec3& vector)
			{
				this->x *= vector.x;
				this->y *= vector.y;
				this->z *= vector.z;

				return *this;
			}

			vec3& Divide(const vec3& vector)
			{
				this->x /= vector.x;
				this->y /= vector.y;
				this->z /= vector.z;

				return *this;
			}

			vec3& operator+=(const vec3& other)
			{
				return this->Add(other);
			}

			vec3& operator-=(const vec3& other)
			{
				return this->Subtract(other);
			}

			vec3& operator*=(const vec3& other)
			{
				return this->Multiply(other);
			}

			vec3& operator/=(const vec3& other)
			{
				return this->Divide(other);
			}

			vec3 operator+(const vec3& v2)
			{
				return this->Add(v2);
			}

			vec3 operator-(const vec3& v2)
			{
				return this->Subtract(v2);
			}

			vec3 operator*(const vec3& v2)
			{
				return this->Multiply(v2);
			}

			vec3 operator/(const vec3& v2)
			{
				return this->Divide(v2);
			}

			float Magnitude() const
			{
				return x* x + y * y + z * z;
			}
		};

		typedef vec3<float> vec3f;
		typedef vec3<double> vec3d;
	}
}
