/*
===========================================================================
Matrix4.cpp

Implements the Matrix4 class
===========================================================================
*/

#define _USE_MATH_DEFINES
#include <string>
#include "Matrix4.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "System/Log.h"
#include "Converters.h"

using namespace s3dge;

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
		data[i] = 0;
}

Matrix4::Matrix4(const float value)
{
	for (int i = 0; i < 16; i++)
		data[i] = 0;

	data[4 * 0 + 0] = value;
	data[4 * 1 + 1] = value;
	data[4 * 2 + 2] = value;
	data[4 * 3 + 3] = value;
}

Matrix4::Matrix4(const Matrix4& ref)
{
	for (int i = 0; i < 16; i++)
		data[i] = ref.data[i];
}

Matrix4& Matrix4::Multiply(const Matrix4& other)
{
	for (int column = 0; column < 4; column++)
	{
		for (int row = 0; row < 4; row++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
				sum += data[row + e * 4] * other.data[e + column * 4];
			data[row + column * 4] = sum;
		}
	}
	return *this;
}

Matrix4& Matrix4::Invert()
{
	float inverted[16];

	inverted[0] = data[5] * data[10] * data[15] -
		data[5] * data[11] * data[14] -
		data[9] * data[6] * data[15] +
		data[9] * data[7] * data[14] +
		data[13] * data[6] * data[11] -
		data[13] * data[7] * data[10];

	inverted[4] = -data[4] * data[10] * data[15] +
		data[4] * data[11] * data[14] +
		data[8] * data[6] * data[15] -
		data[8] * data[7] * data[14] -
		data[12] * data[6] * data[11] +
		data[12] * data[7] * data[10];

	inverted[8] = data[4] * data[9] * data[15] -
		data[4] * data[11] * data[13] -
		data[8] * data[5] * data[15] +
		data[8] * data[7] * data[13] +
		data[12] * data[5] * data[11] -
		data[12] * data[7] * data[9];

	inverted[12] = -data[4] * data[9] * data[14] +
		data[4] * data[10] * data[13] +
		data[8] * data[5] * data[14] -
		data[8] * data[6] * data[13] -
		data[12] * data[5] * data[10] +
		data[12] * data[6] * data[9];

	inverted[1] = -data[1] * data[10] * data[15] +
		data[1] * data[11] * data[14] +
		data[9] * data[2] * data[15] -
		data[9] * data[3] * data[14] -
		data[13] * data[2] * data[11] +
		data[13] * data[3] * data[10];

	inverted[5] = data[0] * data[10] * data[15] -
		data[0] * data[11] * data[14] -
		data[8] * data[2] * data[15] +
		data[8] * data[3] * data[14] +
		data[12] * data[2] * data[11] -
		data[12] * data[3] * data[10];

	inverted[9] = -data[0] * data[9] * data[15] +
		data[0] * data[11] * data[13] +
		data[8] * data[1] * data[15] -
		data[8] * data[3] * data[13] -
		data[12] * data[1] * data[11] +
		data[12] * data[3] * data[9];

	inverted[13] = data[0] * data[9] * data[14] -
		data[0] * data[10] * data[13] -
		data[8] * data[1] * data[14] +
		data[8] * data[2] * data[13] +
		data[12] * data[1] * data[10] -
		data[12] * data[2] * data[9];

	inverted[2] = data[1] * data[6] * data[15] -
		data[1] * data[7] * data[14] -
		data[5] * data[2] * data[15] +
		data[5] * data[3] * data[14] +
		data[13] * data[2] * data[7] -
		data[13] * data[3] * data[6];

	inverted[6] = -data[0] * data[6] * data[15] +
		data[0] * data[7] * data[14] +
		data[4] * data[2] * data[15] -
		data[4] * data[3] * data[14] -
		data[12] * data[2] * data[7] +
		data[12] * data[3] * data[6];

	inverted[10] = data[0] * data[5] * data[15] -
		data[0] * data[7] * data[13] -
		data[4] * data[1] * data[15] +
		data[4] * data[3] * data[13] +
		data[12] * data[1] * data[7] -
		data[12] * data[3] * data[5];

	inverted[14] = -data[0] * data[5] * data[14] +
		data[0] * data[6] * data[13] +
		data[4] * data[1] * data[14] -
		data[4] * data[2] * data[13] -
		data[12] * data[1] * data[6] +
		data[12] * data[2] * data[5];

	inverted[3] = -data[1] * data[6] * data[11] +
		data[1] * data[7] * data[10] +
		data[5] * data[2] * data[11] -
		data[5] * data[3] * data[10] -
		data[9] * data[2] * data[7] +
		data[9] * data[3] * data[6];

	inverted[7] = data[0] * data[6] * data[11] -
		data[0] * data[7] * data[10] -
		data[4] * data[2] * data[11] +
		data[4] * data[3] * data[10] +
		data[8] * data[2] * data[7] -
		data[8] * data[3] * data[6];

	inverted[11] = -data[0] * data[5] * data[11] +
		data[0] * data[7] * data[9] +
		data[4] * data[1] * data[11] -
		data[4] * data[3] * data[9] -
		data[8] * data[1] * data[7] +
		data[8] * data[3] * data[5];

	inverted[15] = data[0] * data[5] * data[10] -
		data[0] * data[6] * data[9] -
		data[4] * data[1] * data[10] +
		data[4] * data[2] * data[9] +
		data[8] * data[1] * data[6] -
		data[8] * data[2] * data[5];

	const float determinant = data[0] * inverted[0] + data[1] * inverted[4] + data[2] * inverted[8] + data[3] * inverted[12];

	if (determinant == 0)
	{
		LOG_ERROR("Determinant was zero!");
		abort();
	}

	const float determinantInverted = 1.0f / determinant;

	for (int i = 0; i < 16; i++)
		data[i] = inverted[i] * determinantInverted;

	return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	*this = Multiply(other);
	return *this;
}

Matrix4 s3dge::operator*(const Matrix4& left, const Matrix4& right)
{
	Matrix4 result(left);
	return result.Multiply(right);
}

Matrix4 Matrix4::Translate(const Vector3& vector)
{
	Matrix4 result = Matrix4::GetIdentity();

	result.data[4 * 3 + 0] = vector.x;
	result.data[4 * 3 + 1] = vector.y;
	result.data[4 * 3 + 2] = vector.z;

	return result;
}

Matrix4 Matrix4::Rotate(const Vector3& axis, float angle)
{
	Matrix4 result = GetIdentity();

	const float angleRad = DegToRad(angle);

	Quaternion q;
	q.w = cos(angleRad / 2);
	q.x = axis.x * sin(angleRad / 2);
	q.y = axis.y * sin(angleRad / 2);
	q.z = axis.z * sin(angleRad / 2);

	result.data[4 * 0 + 0] = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
	result.data[4 * 0 + 1] = 2 * q.x * q.y + 2 * q.w * q.z;
	result.data[4 * 0 + 2] = 2 * q.x * q.z - 2 * q.w * q.y;
	result.data[4 * 1 + 0] = 2 * q.x * q.y - 2 * q.w * q.z;
	result.data[4 * 1 + 1] = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
	result.data[4 * 1 + 2] = 2 * q.y * q.z - 2 * q.w * q.x;
	result.data[4 * 2 + 0] = 2 * q.x * q.z + 2 * q.w * q.y;
	result.data[4 * 2 + 1] = 2 * q.y * q.z + 2 * q.w * q.x;
	result.data[4 * 2 + 2] = 1 - 2 * q.x * q.x - 2 * q.y * q.y;

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

Matrix4 Matrix4::GetPerspective(float fov, float aspect, float near, float far)
{
	Matrix4 result = Matrix4::GetIdentity();

	float frustumDepth = far - near;
	float oneDivByDepth = 1 / frustumDepth;
	float fovRad = DegToRad(fov);

	result.data[4 * 1 + 1] = 1 / tan(0.5f * fovRad);
	result.data[4 * 0 + 0] = result.data[1 * 4 + 1] / aspect;
	result.data[4 * 2 + 2] = far * oneDivByDepth;
	result.data[4 * 3 + 2] = (-far * near) * oneDivByDepth;
	result.data[4 * 2 + 3] = 1;

	return result;
}

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 f(Vector3::Normalize(target - eye));
	Vector3 s(Vector3::Normalize(Vector3::GetCrossProduct(f, up)));
	Vector3 u(Vector3::Normalize(Vector3::GetCrossProduct(s, f)));

	Matrix4 result = GetIdentity();
	result.data[4 * 0 + 0] = s.x;
	result.data[4 * 1 + 0] = s.y;
	result.data[4 * 2 + 0] = s.z;
	result.data[4 * 0 + 1] = u.x;
	result.data[4 * 1 + 1] = u.y;
	result.data[4 * 2 + 1] = u.z;
	result.data[4 * 0 + 2] = f.x;
	result.data[4 * 1 + 2] = f.y;
	result.data[4 * 2 + 2] = f.z;

	return result * Translate(Vector3(-target.x, -target.y, -target.z));
}

cstring Matrix4::Print()
{
	std::string result;

	for (int i = 0; i < 16; i++)
		result += data[i] + i == 15 ? "" : " ";

	return result.c_str();
}



/*float L = pow(vector.GetLength(), 2);
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
result.data[4 * 2 + 2] = (float)((w2 + (u2 + v2) * c) / L);*/