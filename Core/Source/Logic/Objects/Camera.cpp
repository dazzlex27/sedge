/*
===========================================================================
Camera.cpp

Implements the Camera class.
===========================================================================
*/

#include "Camera.h"

using namespace s3dge;
using namespace math;

Camera::Camera()
{
	rotation = Vector3(0, 0, 0);
	_fov = 45.0f;
	_aspectRatio = 16 / 9.0f;
	_near = 0.1f;
	_far = 100.0f;
	_lookAt = Vector3(0, 0, 0);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	projection = Matrix4::GetPerspective(_fov, _aspectRatio, _near, _far);
}

void Camera::SetPosition(const Vector3& position)
{
	// TODO
	Update();
}

void Camera::SetViewDirection(const Vector3& lookAt)
{
	_lookAt = lookAt;
	Update();
}

void Camera::SetFOV(float fov)
{
	_fov = fov;
	Update();
}

void Camera::SetAspectRatio(float aspectRatio)
{
	_aspectRatio = aspectRatio;
	Update();
}

void Camera::SetNear(float near)
{
	_near = near;
	Update();
}

void Camera::SetFar(float far)
{
	_far = far;
	Update();
}

Matrix4 Camera::GetTransformation() const
{
	return Matrix4::GetIdentity();
}