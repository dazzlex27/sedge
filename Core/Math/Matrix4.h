/*
===========================================================================
Matrix4.h

Declares Matrix4 class for scene transformations

!!! ATTENTION !!!
THE MAT USES COLUMN-MAJOR ORDER

Memory layout:

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

#include <CustomTypes.h>

namespace s3dge
{
	struct Vector3;

	struct Matrix4
	{
		float data[16];

		Matrix4();
		Matrix4(const float value);
		Matrix4(const Matrix4& ref);

		Matrix4& Multiply(const Matrix4& other);
		Matrix4& Translate(const Vector3& vector);
		Matrix4& Rotate(const Vector3& axis, const float angleRad);
		Matrix4& Scale(const Vector3& vector);

		Matrix4& operator*=(const Matrix4& other);

		friend Matrix4 operator*(const Matrix4& left, const Matrix4& right);

		static Matrix4 GetTranslation(const Vector3& vector);

		static Matrix4 GetRotation(const Vector3& axis, float angle);

		static Matrix4 GetScale(const Vector3& vector);

		static Matrix4 GetIdentity();

		static Matrix4 GetOrthographic(const float left, const float right, const float bottom, const float top, const float near, const float far);

		static Matrix4 GetPerspective(const float fov, const float aspectRatio, const float near, const float far);

		static Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

		const char*const Print();
	};
}