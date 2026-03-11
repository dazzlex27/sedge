/*
===========================================================================
FPSCamera.cpp

Implements the FPSCamera class.
===========================================================================
*/

#include "FPSCamera.h"

using namespace sedge;

FPSCamera::FPSCamera()
	: Camera()
{
}

FPSCamera::FPSCamera(float fov, float aspectRatio, float near, float far, const Vector3& viewDirection, const Vector3& up)
	: Camera(fov, aspectRatio, near, far, viewDirection, up)
{
}

FPSCamera::~FPSCamera()
{
}