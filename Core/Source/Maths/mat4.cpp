#include "mat4.h"

namespace S3DGE
{
	namespace Maths
	{
		mat4::mat4()
		{
			for (int i = 0; i < 16; i++)
				this->elements[i] = 0;
		}

		mat4::mat4(float value)
		{
			for (int i = 0; i < 16; i++)
				this->elements[i] = 0;

			elements[4 * 0 + 0] = value;
			elements[4 * 1 + 1] = value;
			elements[4 * 2 + 2] = value;
			elements[4 * 3 + 3] = value;
		}

		mat4 mat4::Multiply(const mat4& other)
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
			return result;
		}

		mat4 mat4::operator*(const mat4& matrix)
		{
			return this->Multiply(matrix);
		}

		mat4& mat4::operator*=(const mat4& other)
		{
			*this = this->Multiply(other);
			return *this;
		}

		mat4 mat4::GetIdentity()
		{
			return mat4(1.0f);
		}

		mat4 mat4::Translate(const vec3f& vector)
		{
			mat4 result = mat4::GetIdentity();

			result.elements[4 * 3 + 0] = vector.x;
			result.elements[4 * 3 + 1] = vector.y;
			result.elements[4 * 3 + 2] = vector.z;

			return result;
		}

		mat4 mat4::Rotate(const vec3f& vector, float angle)
		{
			mat4 result = mat4::GetIdentity();

			float L = vector.Magnitude();
			float angleR = -(float)(angle * M_PI / 180.0);
			float c = (float)cos(angleR);
			float s = (float)sin(angleR);
			float u = vector.x;
			float v = vector.y;
			float w = vector.z;
			float u2 = vector.x * vector.x;
			float v2 = vector.y * vector.y;
			float w2 = vector.z * vector.z;

			result.elements[4 * 0 + 0] = (float)((u2 + (v2 + w2) * c) / L);
			result.elements[4 * 0 + 1] = (float)((u * v * (1 - c) - w * sqrt(L) * s) / L);
			result.elements[4 * 0 + 2] = (float)((u * w * (1 - c) + v * sqrt(L) * s) / L);

			result.elements[4 * 1 + 0] = (float)((u * v * (1 - c) + w * sqrt(L) * s) / L);
			result.elements[4 * 1 + 1] = (float)((v2 + (u2 + w2) * c) / L);
			result.elements[4 * 1 + 2] = (float)((v * w * (1 - c) - u * sqrt(L) * s) / L);

			result.elements[4 * 2 + 0] = (float)((u * w * (1 - c) - v * sqrt(L) * s) / L);
			result.elements[4 * 2 + 1] = (float)((v * w * (1 - c) + u * sqrt(L) * s) / L);
			result.elements[4 * 2 + 2] = (float)((w2 + (u2 + v2) * c) / L);

			return result;
		}

		mat4 mat4::Scale(const vec3f& vector)
		{
			mat4 result = mat4::GetIdentity();

			result.elements[4 * 0 + 0] = vector.x;
			result.elements[4 * 1 + 1] = vector.y;
			result.elements[4 * 2 + 2] = vector.z;

			return result;
		}

		mat4 mat4::GetOrthographic(float left, float right, float bottom, float top, float near, float far)
		{
			mat4 result = mat4::GetIdentity();

			result.elements[4 * 0 + 0] = 2 / (right - left);
			result.elements[4 * 1 + 1] = 2 / (top - bottom);
			result.elements[4 * 2 + 2] = -2 / (far - near);

			result.elements[4 * 3 + 0] = -(right + left) / (right - left);
			result.elements[4 * 3 + 1] = -(top + bottom) / (top - bottom);
			result.elements[4 * 3 + 2] = -(far + near) / (far - near);

			return result;
		}

		mat4 mat4::GetPerspective(float fov, float aspectRatio, float near, float far)
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
	}
}