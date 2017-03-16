/*
===========================================================================
Matrix4.h

Declares Matrix4 class for scene transformations

!!! ATTENTION !!!
THE MAT USES COLUMN-MAJOR ORDER

Example:
Memory layout: 0 1 2 3 4 5 6 7 8 9

Column Major:
0 3 6
1 4 7
2 5 8

Row Major:
0 1 2
3 4 5
6 7 8
===========================================================================
*/

#pragma once

#include "Vector3.h"
#include <cmath>

namespace s3dge
{
	namespace math
	{
		template <typename T>
		struct Matrix4
		{
			T elements[16];

			Matrix4()
			{
				for (int i = 0; i < 16; i++)
					this->elements[i] = 0;
			}

			Matrix4(T value)
			{
				for (int i = 0; i < 16; i++)
					this->elements[i] = 0;

				elements[4 * 0 + 0] = value;
				elements[4 * 1 + 1] = value;
				elements[4 * 2 + 2] = value;
				elements[4 * 3 + 3] = value;
			}

			Matrix4 Multiply(const Matrix4& other)
			{
				Matrix4<T> result;

				for (int column = 0; column < 4; column++)
				{
					for (int row = 0; row < 4; row++)
					{
						float sum = 0.0f;
						for (int e = 0; e < 4; e++)
							sum += elements[row + e * 4] * other.elements[e + column * 4];
						result.elements[row + column * 4] = sum;
					}
				}
				return result;
			}

			Matrix4 operator*(const Matrix4& matrix)
			{
				return this->Multiply(matrix);
			}

			Matrix4& operator*=(const Matrix4& other)
			{
				*this = this->Multiply(other);
				return *this;
			}

			/*
			=============================================
			Returns a matrix translated according to the input vector
			Looks like this:
			1 0 0 x
			0 1 0 y
			0 0 1 z
			0 0 0 1
			=============================================
			*/
			static Matrix4 Translate(const Vector3<T>& vector)
			{
				Matrix4<T> result = Matrix4<T>::GetIdentity();

				result.elements[4 * 3 + 0] = vector.x;
				result.elements[4 * 3 + 1] = vector.y;
				result.elements[4 * 3 + 2] = vector.z;

				return result;
			}

			/*
			=============================================
			Returns a matrix rotated according to the specified input parameters
			Too big to fit its looks here, feel free to google it
			=============================================
			*/
			static Matrix4 Rotate(const Vector3<T>& vector, T angle)
			{
				Matrix4<T> result = Matrix4<T>::GetIdentity();

				T L = vector.Magnitude();
				T angleR = -(T)(angle * M_PI / 180.0);
				T c = (T)cos(angleR);
				T s = (T)sin(angleR);
				T u = vector.x;
				T v = vector.y;
				T w = vector.z;
				T u2 = vector.x * vector.x;
				T v2 = vector.y * vector.y;
				T w2 = vector.z * vector.z;

				result.elements[4 * 0 + 0] = (T)((u2 + (v2 + w2) * c) / L);
				result.elements[4 * 0 + 1] = (T)((u * v * (1 - c) - w * sqrt(L) * s) / L);
				result.elements[4 * 0 + 2] = (T)((u * w * (1 - c) + v * sqrt(L) * s) / L);

				result.elements[4 * 1 + 0] = (T)((u * v * (1 - c) + w * sqrt(L) * s) / L);
				result.elements[4 * 1 + 1] = (T)((v2 + (u2 + w2) * c) / L);
				result.elements[4 * 1 + 2] = (T)((v * w * (1 - c) - u * sqrt(L) * s) / L);

				result.elements[4 * 2 + 0] = (T)((u * w * (1 - c) - v * sqrt(L) * s) / L);
				result.elements[4 * 2 + 1] = (T)((v * w * (1 - c) + u * sqrt(L) * s) / L);
				result.elements[4 * 2 + 2] = (T)((w2 + (u2 + v2) * c) / L);

				return result;
			}

			/*
			=============================================
			Returns a matrix scaled by the input vector
			Looks like this:
			x 0 0 0
			0 y 0 0
			0 0 z 0
			0 0 0 1
			=============================================
			*/
			static Matrix4 Scale(const Vector3<T>& vector)
			{
				{
					Matrix4<T> result = Matrix4<T>::GetIdentity();

					result.elements[4 * 0 + 0] = vector.x;
					result.elements[4 * 1 + 1] = vector.y;
					result.elements[4 * 2 + 2] = vector.z;

					return result;
				}
			}

			/*
			=============================================
			Returns an identity matrix
			Looks like this:
			1 0 0 0
			0 1 0 0
			0 0 1 0
			0 0 0 1
			=============================================
			*/
			static Matrix4 GetIdentity()
			{
				return Matrix4<T>(1);
			}

			/*
			=============================================
			Returns orthographic projection according to specified limits
			Looks like this:
			2/(r-l)		0			0			-(r+l)/(r-l)
			0			2/(t-b)		0			-(t+b)/(t-b)
			0			0			-2/(f-n)	-(f+n)/(f-n)
			0			0			0			1

			=============================================
			*/
			static Matrix4 GetOrthographic(T left, T right, T bottom, T top, T near, T far)
			{
				Matrix4<T> result = Matrix4<T>::GetIdentity();

				result.elements[4 * 0 + 0] = 2 / (right - left);
				result.elements[4 * 1 + 1] = 2 / (top - bottom);
				result.elements[4 * 2 + 2] = -2 / (far - near);

				result.elements[4 * 3 + 0] = -(right + left) / (right - left);
				result.elements[4 * 3 + 1] = -(top + bottom) / (top - bottom);
				result.elements[4 * 3 + 2] = -(far + near) / (far - near);

				return result;
			}

			/*
			Returns a perspective matrix with the specified settings
			Looks like this:
			2n/(r-l)	0			(r+l)/(r-l)		0
			0			2n(t-b)		(t+b)/(t-b)		0
			0			0			-(f+n)/(f-n)	-2fn(f-n)/(f-n)
			0			0			-1				0
			*/
			static Matrix4 GetPerspective(T fov, T aspectRatio, T near, T far)
			{
				Matrix4<T> result = Matrix4<T>::GetIdentity();

				float q = 1.0f / tan(toRadians(0.5f * fov));
				float a = q / aspectRatio;

				float b = (near + far) / (near - far);
				float c = (2.0f * near * far) / (near - far);

				result.elements[0 + 0 * 4] = a;
				result.elements[1 + 1 * 4] = q;
				result.elements[2 + 2 * 4] = b;
				result.elements[2 + 3 * 4] = -1.0f;
				result.elements[3 + 2 * 4] = c;

				return result;
			}

			inline static float toRadians(float degrees)
			{
				return (float)(degrees * (3.14 / 180.0f));
			}
		};

		typedef Matrix4<float> mat4;
	}
}