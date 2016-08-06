#pragma once

#include <math.h>

namespace S3DGE
{
	namespace Maths
	{
		struct mat4 // Column-major
		{
			float elements[16];

			mat4()
			{
				for (int i = 0; i < 16; i++)
					this->elements[i] = 0;
			}

			mat4(float value)
			{
				for (int i = 0; i < 16;i++)
					this->elements[i] = 0;

				elements[4 * 0 + 0] = value;
				elements[4 * 1 + 1] = value;
				elements[4 * 2 + 2] = value;
				elements[4 * 3 + 3] = value;
			}

			mat4& Multiply(const mat4& other)
			{
				mat4 result;

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
				*this = result;

				return *this;
			}

			mat4 operator*(const mat4& matrix)
			{
				return this->Multiply(matrix);
			}

			mat4& operator*=(const mat4& other)
			{
				return this->Multiply(other);
			}

			static mat4 GetIdentity()
			{
				return mat4(1.0f);
			}

			static mat4 Translate(const vec3f& vector)
			{
				mat4 result = mat4::GetIdentity();

				result.elements[4 * 3 + 0] = vector.x;
				result.elements[4 * 3 + 1] = vector.y;
				result.elements[4 * 3 + 2] = vector.z;

				return result;
			}

			static mat4 Rotate(const vec3f& vector, double angle)
			{
				mat4 result = mat4::GetIdentity();

				float L = vector.Magnitude();
				float angleR = (float)(angle * M_PI / 180.0); //converting to radian value
				float u = vector.x;
				float v = vector.y;
				float w = vector.z;
				float u2 = vector.x * vector.x;
				float v2 = vector.y * vector.y;
				float w2 = vector.z * vector.z;

				result.elements[4 * 0 + 0] = (u2 + (v2 + w2) * cos(angleR)) / L;
				result.elements[4 * 0 + 1] = (u * v * (1 - cos(angleR)) - w * sqrt(L) * sin(angleR)) / L;
				result.elements[4 * 0 + 2] = (u * w * (1 - cos(angleR)) + v * sqrt(L) * sin(angleR)) / L;

				result.elements[4 * 1 + 0] = (u * v * (1 - cos(angleR)) + w * sqrt(L) * sin(angleR)) / L;
				result.elements[4 * 1 + 1] = (v2 + (u2 + w2) * cos(angleR)) / L;
				result.elements[4 * 1 + 2] = (v * w * (1 - cos(angleR)) - u * sqrt(L) * sin(angleR)) / L;

				result.elements[4 * 2 + 0] = (u * w * (1 - cos(angleR)) - v * sqrt(L) * sin(angleR)) / L;
				result.elements[4 * 2 + 1] = (v * w * (1 - cos(angleR)) + u * sqrt(L) * sin(angleR)) / L;
				result.elements[4 * 2 + 2] = (w2 + (u2 + v2) * cos(angleR)) / L;

				return result;
			}

			static mat4 Scale(const vec3f& vector)
			{
				mat4 result = mat4::GetIdentity();

				result.elements[4 * 0 + 0] = vector.x;
				result.elements[4 * 1 + 1] = vector.y;
				result.elements[4 * 2 + 2] = vector.z;

				return result;
			}

			static mat4 GetOrthographic(float left, float right, float top, float bottom, float near, float far)
			{
				mat4 result = mat4::GetIdentity();

				result.elements[4 * 0 + 0] = 2 / (right - left);
				result.elements[4 * 1 + 1] = 2 / (top - bottom);
				result.elements[4 * 2 + 2] = -2 / (far - near);

				result.elements[4 * 3 + 0] = - (right + left) / (right - left);
				result.elements[4 * 3 + 1] = - (top + bottom) / (top - bottom);
				result.elements[4 * 3 + 2] = - (far + near) / (far - near);

				return result;
			}

			static mat4 GetPerspective(float fov, float aspectRatio, float near, float far)
			{
				mat4 result;

				float top = (float)(near*((M_PI / 180) * (fov / 2)));
				float bottom = -top;
				float right = top * aspectRatio;
				float left = -right;

				result.elements[4 * 0 + 0] = (2 * near) / (right - left);
				result.elements[4 * 1 + 1] = (2 * near) / (top - bottom);
				result.elements[4 * 2 + 2] = -(far + near) / (far - near);

				result.elements[4 * 2 + 0] = (right + left) / (right - left);
				result.elements[4 * 2 + 1] = (top + bottom) / (top - bottom);
				result.elements[4 * 2 + 3] = -1;
				result.elements[4 * 3 + 2] = -(2 * far * near) / (far - near);

				return result;
			}
		};
	}
}