/*
===========================================================================
FPSCamera.h

Defines a class for first-person camera.
===========================================================================
*/

#pragma once

#include "Camera.h"

namespace sedge
{
	class FPSCamera : public Camera
	{
	public:
		FPSCamera();
		FPSCamera(float fov, float aspectRatio, float near, float far, const Vector3& viewDirection = Vector3(0, 0, -1), const Vector3& up = Vector3(0, 1, 0));
		virtual ~FPSCamera();
	};
}