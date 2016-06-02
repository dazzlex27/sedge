/*
===========================================================================
TPSCamera.h

Defines a class for third-person camera.
===========================================================================
*/

#pragma once

#include "Camera.h"

namespace s3dge
{
	class TPSCamera : public Camera
	{
	protected:
		Vector3 Offset;

	public:
		TPSCamera();
		TPSCamera(float fov, float aspectRatio, float near, float far, const Vector3& viewDirection = Vector3(0, 0, -1), const Vector3& up = Vector3(0, 1, 0));
		virtual ~TPSCamera();

		const Vector3& GetOffset() const { return Offset; }
		void SetOffset(const Vector3& offset);

	protected:
		virtual void UpdateView() override;
	};
}