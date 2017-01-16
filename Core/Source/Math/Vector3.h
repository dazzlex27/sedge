/*
===========================================================================
Vector3.h

Implements a 3-component vector class
===========================================================================
*/

#pragma once

namespace s3dge
{
	namespace math
	{
		template <typename T>
		struct Vector3
		{
			T x;
			T y;
			T z;

			Vector3()
				: x(0), y(0), z(0) {}

			Vector3(T x, T y, T z)
				: x(x), y(y), z(z) {}

			Vector3& Add(const Vector3& vector)
			{
				this->x += vector.x;
				this->y += vector.y;
				this->z += vector.z;

				return *this;
			}

			Vector3& Subtract(const Vector3& vector)
			{
				this->x -= vector.x;
				this->y -= vector.y;
				this->z -= vector.z;

				return *this;
			}

			Vector3& Multiply(const Vector3& vector)
			{
				this->x *= vector.x;
				this->y *= vector.y;
				this->z *= vector.z;

				return *this;
			}

			Vector3& Divide(const Vector3& vector)
			{
				this->x /= vector.x;
				this->y /= vector.y;
				this->z /= vector.z;

				return *this;
			}

			Vector3& operator+=(const Vector3& other)
			{
				return this->Add(other);
			}

			Vector3& operator-=(const Vector3& other)
			{
				return this->Subtract(other);
			}

			Vector3& operator*=(const Vector3& other)
			{
				return this->Multiply(other);
			}

			Vector3& operator/=(const Vector3& other)
			{
				return this->Divide(other);
			}

			Vector3 operator+(const Vector3& v2)
			{
				return this->Add(v2);
			}

			Vector3 operator-(const Vector3& v2)
			{
				return this->Subtract(v2);
			}

			Vector3 operator*(const Vector3& v2)
			{
				return this->Multiply(v2);
			}

			Vector3 operator/(const Vector3& v2)
			{
				return this->Divide(v2);
			}

			float Magnitude() const
			{
				return x* x + y * y + z * z;
			}
		};

		typedef Vector3<float> vec3f;
		typedef Vector3<double> vec3d;
	}
}
