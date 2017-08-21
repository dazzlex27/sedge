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

#include "CustomTypes.h"

namespace s3dge
{
	struct Vector3;
	struct Quaternion;

	struct Matrix4
	{
		float data[16];

		Matrix4();
		Matrix4(const float value);
		Matrix4(const Matrix4& ref);

		Matrix4& Multiply(const Matrix4& other);

		Matrix4& Invert();

		Matrix4& operator*=(const Matrix4& other);

		friend Matrix4 operator*(const Matrix4& left, const Matrix4& right);

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
		static Matrix4 GetTranslation(const Vector3& vector);

		/*
		=============================================
		Returns a matrix rotated according to the specified input parameters
		Too big to fit its looks here, feel free to google it
		=============================================
		*/
		static Matrix4 GetRotation(const Vector3& axis, float angle);

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
		static Matrix4 GetScale(const Vector3& vector);

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
		static Matrix4 GetIdentity();

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
		static Matrix4 GetOrthographic(const float left, const float right, const float bottom, const float top, const float near, const float far);

		/*
		Returns a perspective matrix with the specified settings
		Looks like this:
		uh = Cot( fov/2 ) == 1/Tan(fov/2)
		uw / uh = 1/aspect

		uw        0       0       0
		0		  uh      0       0
		0         0      f/(f-n)  1
		0         0    -fn/(f-n)  0
		*/
		static Matrix4 GetPerspective(const float fov, const float aspectRatio, const float near, const float far);

		/*
		=============================================
		Returns lookAt matrix for a set of position, view direction and up vectors 
		Looks like this:
		Sx			Sy			Sz			-dot(s, eye)
		Fx			Fy			Fz			-dot(u, eye)
		Ux			Uy			Uz			dot(f, eye)
		0			0			0			1

		=============================================
		*/
		static Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

		const char* Print();
	};
}