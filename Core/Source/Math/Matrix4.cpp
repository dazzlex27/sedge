#define _USE_MATH_DEFINES
#include "Matrix4.h"
#include "Vector3.h"
#include "Internal/Log.h"

using namespace s3dge;
using namespace math;

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
		data[i] = 0;
}

Matrix4::Matrix4(float value)
{
	for (int i = 0; i < 16; i++)
		data[i] = 0;

	data[4 * 0 + 0] = value;
	data[4 * 1 + 1] = value;
	data[4 * 2 + 2] = value;
	data[4 * 3 + 3] = value;
}

Matrix4 Matrix4::Multiply(const Matrix4& other)
{
	Matrix4 result;

	for (int column = 0; column < 4; column++)
	{
		for (int row = 0; row < 4; row++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
				sum += data[row + e * 4] * other.data[e + column * 4];
			result.data[row + column * 4] = sum;
		}
	}
	return result;
}

Matrix4& Matrix4::Invert()
{
	float inv[16], det;
	int i;

	inv[0] = data[5] * data[10] * data[15] -
		data[5] * data[11] * data[14] -
		data[9] * data[6] * data[15] +
		data[9] * data[7] * data[14] +
		data[13] * data[6] * data[11] -
		data[13] * data[7] * data[10];

	inv[4] = -data[4] * data[10] * data[15] +
		data[4] * data[11] * data[14] +
		data[8] * data[6] * data[15] -
		data[8] * data[7] * data[14] -
		data[12] * data[6] * data[11] +
		data[12] * data[7] * data[10];

	inv[8] = data[4] * data[9] * data[15] -
		data[4] * data[11] * data[13] -
		data[8] * data[5] * data[15] +
		data[8] * data[7] * data[13] +
		data[12] * data[5] * data[11] -
		data[12] * data[7] * data[9];

	inv[12] = -data[4] * data[9] * data[14] +
		data[4] * data[10] * data[13] +
		data[8] * data[5] * data[14] -
		data[8] * data[6] * data[13] -
		data[12] * data[5] * data[10] +
		data[12] * data[6] * data[9];

	inv[1] = -data[1] * data[10] * data[15] +
		data[1] * data[11] * data[14] +
		data[9] * data[2] * data[15] -
		data[9] * data[3] * data[14] -
		data[13] * data[2] * data[11] +
		data[13] * data[3] * data[10];

	inv[5] = data[0] * data[10] * data[15] -
		data[0] * data[11] * data[14] -
		data[8] * data[2] * data[15] +
		data[8] * data[3] * data[14] +
		data[12] * data[2] * data[11] -
		data[12] * data[3] * data[10];

	inv[9] = -data[0] * data[9] * data[15] +
		data[0] * data[11] * data[13] +
		data[8] * data[1] * data[15] -
		data[8] * data[3] * data[13] -
		data[12] * data[1] * data[11] +
		data[12] * data[3] * data[9];

	inv[13] = data[0] * data[9] * data[14] -
		data[0] * data[10] * data[13] -
		data[8] * data[1] * data[14] +
		data[8] * data[2] * data[13] +
		data[12] * data[1] * data[10] -
		data[12] * data[2] * data[9];

	inv[2] = data[1] * data[6] * data[15] -
		data[1] * data[7] * data[14] -
		data[5] * data[2] * data[15] +
		data[5] * data[3] * data[14] +
		data[13] * data[2] * data[7] -
		data[13] * data[3] * data[6];

	inv[6] = -data[0] * data[6] * data[15] +
		data[0] * data[7] * data[14] +
		data[4] * data[2] * data[15] -
		data[4] * data[3] * data[14] -
		data[12] * data[2] * data[7] +
		data[12] * data[3] * data[6];

	inv[10] = data[0] * data[5] * data[15] -
		data[0] * data[7] * data[13] -
		data[4] * data[1] * data[15] +
		data[4] * data[3] * data[13] +
		data[12] * data[1] * data[7] -
		data[12] * data[3] * data[5];

	inv[14] = -data[0] * data[5] * data[14] +
		data[0] * data[6] * data[13] +
		data[4] * data[1] * data[14] -
		data[4] * data[2] * data[13] -
		data[12] * data[1] * data[6] +
		data[12] * data[2] * data[5];

	inv[3] = -data[1] * data[6] * data[11] +
		data[1] * data[7] * data[10] +
		data[5] * data[2] * data[11] -
		data[5] * data[3] * data[10] -
		data[9] * data[2] * data[7] +
		data[9] * data[3] * data[6];

	inv[7] = data[0] * data[6] * data[11] -
		data[0] * data[7] * data[10] -
		data[4] * data[2] * data[11] +
		data[4] * data[3] * data[10] +
		data[8] * data[2] * data[7] -
		data[8] * data[3] * data[6];

	inv[11] = -data[0] * data[5] * data[11] +
		data[0] * data[7] * data[9] +
		data[4] * data[1] * data[11] -
		data[4] * data[3] * data[9] -
		data[8] * data[1] * data[7] +
		data[8] * data[3] * data[5];

	inv[15] = data[0] * data[5] * data[10] -
		data[0] * data[6] * data[9] -
		data[4] * data[1] * data[10] +
		data[4] * data[2] * data[9] +
		data[8] * data[1] * data[6] -
		data[8] * data[2] * data[5];

	det = data[0] * inv[0] + data[1] * inv[4] + data[2] * inv[8] + data[3] * inv[12];

	if (det == 0)
		LOG_ERROR("Determinant was zero!");

	det = 1.0f / det;

	for (i = 0; i < 16; i++)
		data[i] = inv[i] * det;

	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& matrix)
{
	return this->Multiply(matrix);
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	*this = this->Multiply(other);
	return *this;
}

Matrix4 Matrix4::Translate(const Vector3& vector)
{
	Matrix4 result = Matrix4::GetIdentity();

	result.data[4 * 3 + 0] = vector.x;
	result.data[4 * 3 + 1] = vector.y;
	result.data[4 * 3 + 2] = vector.z;

	return result;
}

Matrix4 Matrix4::Rotate(const Vector3& vector, float angle)
{
	Matrix4 result = Matrix4::GetIdentity();

	float L = pow(vector.GetLength(), 2);
	float angleR = -(float)(angle * M_PI / 180.0);
	float c = (float)cos(angleR);
	float s = (float)sin(angleR);
	float u = vector.x;
	float v = vector.y;
	float w = vector.z;
	float u2 = vector.x * vector.x;
	float v2 = vector.y * vector.y;
	float w2 = vector.z * vector.z;

	result.data[4 * 0 + 0] = (float)((u2 + (v2 + w2) * c) / L);
	result.data[4 * 0 + 1] = (float)((u * v * (1 - c) - w * sqrt(L) * s) / L);
	result.data[4 * 0 + 2] = (float)((u * w * (1 - c) + v * sqrt(L) * s) / L);

	result.data[4 * 1 + 0] = (float)((u * v * (1 - c) + w * sqrt(L) * s) / L);
	result.data[4 * 1 + 1] = (float)((v2 + (u2 + w2) * c) / L);
	result.data[4 * 1 + 2] = (float)((v * w * (1 - c) - u * sqrt(L) * s) / L);

	result.data[4 * 2 + 0] = (float)((u * w * (1 - c) - v * sqrt(L) * s) / L);
	result.data[4 * 2 + 1] = (float)((v * w * (1 - c) + u * sqrt(L) * s) / L);
	result.data[4 * 2 + 2] = (float)((w2 + (u2 + v2) * c) / L);

	return result;
}

Matrix4 Matrix4::Scale(const Vector3& vector)
{
	Matrix4 result = Matrix4::GetIdentity();

	result.data[4 * 0 + 0] = vector.x;
	result.data[4 * 1 + 1] = vector.y;
	result.data[4 * 2 + 2] = vector.z;

	return result;
}

Matrix4 Matrix4::GetIdentity()
{
	return Matrix4(1);
}

Matrix4 Matrix4::GetOrthographic(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4 result = Matrix4::GetIdentity();

	result.data[4 * 0 + 0] = 2 / (right - left);
	result.data[4 * 1 + 1] = 2 / (top - bottom);
	result.data[4 * 2 + 2] = -2 / (far - near);

	result.data[4 * 3 + 0] = -(right + left) / (right - left);
	result.data[4 * 3 + 1] = -(top + bottom) / (top - bottom);
	result.data[4 * 3 + 2] = -(far + near) / (far - near);

	return result;
}

inline static float ToRadians(float degrees)
{
	return (float)(degrees * (3.14 / 180.0f));
}

Matrix4 Matrix4::GetPerspective(float fov, float aspectRatio, float near, float far)
{
	Matrix4 result = Matrix4::GetIdentity();

	float tanHalfFOV = tanf(ToRadians(fov / 2.0f));

	result.data[4 * 0 + 0] = 1.0f / (tanHalfFOV * aspectRatio);
	result.data[4 * 1 + 1] = 1.0f / tanHalfFOV;
	result.data[4 * 2 + 2] = (-near - far) / (near - far);
	result.data[4 * 2 + 3] = 2.0f * far * near / (near - far);
	//result.data[4 * 3 + 2] = -1.0f;

	return result;
}

Matrix4 Matrix4::GetLookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
{
	Vector3 f((eye - center).Normalize());
	Vector3 u(Vector3(up).Normalize());
	Vector3 s(Vector3::GetCrossProduct(f, u).Normalize());
	u = Vector3::GetCrossProduct(s, f);

	Matrix4 result(1);
	result.data[4 * 0 + 0] = s.x;
	result.data[4 * 0 + 1] = s.y;
	result.data[4 * 0 + 2] = s.z;
	result.data[4 * 1 + 0] = u.x;
	result.data[4 * 1 + 1] = u.y;
	result.data[4 * 1 + 2] = u.z;
	result.data[4 * 2 + 0] = -f.x;
	result.data[4 * 2 + 1] = -f.y;
	result.data[4 * 2 + 2] = -f.z;
	result.data[4 * 3 + 0] = -Vector3::GetDotProduct(s, eye);
	result.data[4 * 3 + 1] = -Vector3::GetDotProduct(u, eye);
	result.data[4 * 3 + 2] = Vector3::GetDotProduct(f, eye);

	return result;

}

std::string Matrix4::Print()
{
	std::string result;

	for (int i = 0; i < 16; i++)
		result += data[i] + i == 15 ? "" : " ";

	return result;
}
