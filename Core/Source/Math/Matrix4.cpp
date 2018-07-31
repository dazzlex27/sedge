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
#include "System/Logger.h"
#include "Converters.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace s3dge;
using namespace std;

static void TranslateMatrix(Matrix4& matrix, const Vector3& vector);
static void RotateMatrix(Matrix4& matrix, const Vector3& axis, const float angle);
static void ScaleMatrix(Matrix4& matrix, const Vector3& vector);

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

Matrix4& Matrix4::Translate(const Vector3& vector)
{
	TranslateMatrix(*this, vector);

	return *this;
}

Matrix4& Matrix4::Rotate(const Vector3& axis, const float angleRad)
{
	RotateMatrix(*this, axis, angleRad);

	return *this;
}

Matrix4& Matrix4::Scale(const Vector3& vector)
{
	ScaleMatrix(*this, vector);

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

Matrix4 Matrix4::GetIdentity()
{
	return Matrix4(1);
}

Matrix4 Matrix4::GetTranslation(const Vector3& vector)
{
	Matrix4 result = Matrix4::GetIdentity();

	TranslateMatrix(result, vector);

	return result;
}

Matrix4 Matrix4::GetRotation(const Vector3& axis, const float angle)
{
	Matrix4 result = GetIdentity();

	const float angleRads = glm::radians(angle);

	RotateMatrix(result, axis, angleRads);

	return result;
}

Matrix4 Matrix4::GetScale(const Vector3& vector)
{
	Matrix4 result = Matrix4::GetIdentity();

	ScaleMatrix(result, vector);

	return result;
}

Matrix4 Matrix4::GetOrthographic(const float left, const float right, const float bottom, const float top, const float near, const float far)
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

Matrix4 Matrix4::GetPerspective(const float fov, const float aspect, const float near, const float far)
{
	Matrix4 result;

	const float fovRads = glm::radians(fov);
	glm::mat4 perspective = glm::perspective(fovRads, aspect, near, far);
	memcpy(&result.data[0], &perspective[0], sizeof(float) * 16);

	return result;
}

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	glm::vec3 gEye(eye.x, eye.y, eye.z);
	glm::vec3 gTarget(target.x, target.y, target.z);
	glm::vec3 gUp(up.x, up.y, up.z);

	glm::mat4 view = glm::lookAt(gEye, gTarget, gUp);

	Matrix4 result;
	memcpy(&result.data[0], &view[0], sizeof(float) * 16);

	return result;
}

const char*const Matrix4::Print()
{
	string result;

	for (int i = 0; i < 16; i++)
		result += data[i] + i == 15 ? "" : " ";

	return result.c_str();
}

void TranslateMatrix(Matrix4& matrix, const Vector3& vector)
{
	matrix.data[4 * 3 + 0] += vector.x;
	matrix.data[4 * 3 + 1] += vector.y;
	matrix.data[4 * 3 + 2] += vector.z;
}

void RotateMatrix(Matrix4& matrix, const Vector3& axis, const float angle)
{
	glm::mat4 gRot;
	memcpy(&gRot[0], &matrix.data[0], sizeof(float) * 16);

	glm::vec3 gAxis(axis.x, axis.y, axis.z);

	glm::mat4 mat = glm::rotate(gRot, angle, gAxis);

	memcpy(&matrix.data[0], &mat[0], sizeof(float) * 16);
}

void ScaleMatrix(Matrix4& matrix, const Vector3& vector)
{
	matrix.data[4 * 0 + 0] *= vector.x;
	matrix.data[4 * 1 + 1] *= vector.y;
	matrix.data[4 * 2 + 2] *= vector.z;
}