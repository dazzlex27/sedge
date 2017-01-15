/*
===========================================================================
Vector4.h

Implements a 4-component vector class
===========================================================================
*/

#pragma once

namespace s3dge
{
	namespace maths
	{
		template <typename T>
		struct Vector4
		{
			T x;
			T y;
			T z;
			T w;

			Vector4()
				: x(0), y(0), z(0), w(0) {}

			Vector4(T x, T y, T z, T w)
				: x(x), y(y), z(z), w(w) {}

			Vector4& Add(const Vector4& vector)
			{
				this->x += vector.x;
				this->y += vector.y;
				this->z += vector.z;
				this->w += vector.w;

				return *this;
			}

			Vector4& Subtract(const Vector4& vector)
			{
				this->x -= vector.x;
				this->y -= vector.y;
				this->z -= vector.z;
				this->w -= vector.w;

				return *this;
			}

			Vector4& Multiply(const Vector4& vector)
			{
				this->x *= vector.x;
				this->y *= vector.y;
				this->z *= vector.z;
				this->w *= vector.w;

				return *this;
			}

			/*vec4& Multiply(const mat4& matrix)
			{
				vec4 result;
				for (int i = 0; i < 4; i++)
					result.x = matrix[0 + 4 * i];
				for (int i = 0; i < 4; i++)
					result.y = matrix[1 + 4 * i];
				for (int i = 0; i < 4; i++)
					result.z = matrix[2 + 4 * i];
				for (int i = 0; i < 4; i++)
					result.w = matrix[3 + 4 * i];

				return result;
			}*/

			Vector4& Divide(const Vector4& vector)
			{
				this->x /= vector.x;
				this->y /= vector.y;
				this->z /= vector.z;
				this->w /= vector.w;

				return *this;
			}

			Vector4& operator+=(const Vector4& other)
			{
				return this->Add(other);
			}

			Vector4& operator-=(const Vector4& other)
			{
				return this->Subtract(other);
			}

			Vector4& operator*=(const Vector4& other)
			{
				return this->Multiply(other);
			}

			Vector4& operator/=(const Vector4& other)
			{
				return this->Divide(other);
			}

			Vector4 operator+(const Vector4& v2)
			{
				return this->Add(v2);
			}

			Vector4 operator-(const Vector4& v2)
			{
				return this->Subtract(v2);
			}

			Vector4 operator*(const Vector4& v2)
			{
				return this->Multiply(v2);
			}

			Vector4 operator/(const Vector4& v2)
			{
				return this->Divide(v2);
			}
		};

		typedef Vector4<float> vec4f;
		typedef Vector4<double> vec4d;
	}
}