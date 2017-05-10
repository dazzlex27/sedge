/*
===========================================================================
TPSCamera.cpp

Implements the TPSCamera class.
===========================================================================
*/

#include "TPSCamera.h"

using namespace s3dge;

TPSCamera::TPSCamera()
	: Camera()
{
}

TPSCamera::TPSCamera(float fov, float aspectRatio, float near, float far, const Vector3& viewDirection, const Vector3& up)
	: Camera(fov, aspectRatio, near, far, viewDirection, up)
{
}

TPSCamera::~TPSCamera()
{
}

void TPSCamera::SetOffset(const Vector3& offset)
{
	Offset = offset;
	UpdateView();
}

void TPSCamera::UpdateView()
{
	ViewMatrix = Matrix4::GetLookAt(Position + Offset, Position + Offset + ViewDirection, Up);
}