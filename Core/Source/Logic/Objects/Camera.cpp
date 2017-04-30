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
	: _fov(90.0f),
	_aspectRatio(16.0f / 9.0f),
	_near(-1.0f),
	_far(10.0f),
	_viewDirection(Vector3(0, 0, 1)),
	_up(Vector3(0, 1, 0))
{
	UpdatePerspective();
}

Camera::Camera(float fov, float aspectRatio, float near, float far, const Vector3& viewDirection, const Vector3& up)
	: _fov(fov),
	_aspectRatio(aspectRatio),
	_near(near),
	_far(far),
	_viewDirection(viewDirection),
	_up(up)
{
	UpdatePerspective();
}

Camera::~Camera()
{
}

void Camera::UpdatePerspective()
{
	_projection = Matrix4::GetPerspective(_fov, _aspectRatio, _near, _far);
}

void Camera::SetPosition(const Point3D& position)
{
	Position = Vector3(position);
	UpdatePerspective();
}

void Camera::SetViewDirection(const Vector3& viewDirection)
{
	_viewDirection = viewDirection;
	UpdatePerspective();
}

void Camera::SetFOV(float fov)
{
	_fov = fov;
	UpdatePerspective();
}

void Camera::SetAspectRatio(float aspectRatio)
{
	_aspectRatio = aspectRatio;
	UpdatePerspective();
}

void Camera::SetNear(float near)
{
	_near = near;
	UpdatePerspective();
}

void Camera::SetFar(float far)
{
	_far = far;
	UpdatePerspective();
}

void Camera::Render()
{

}

void Camera::Update()
{
}

Matrix4 Camera::GetWorldToViewMatrix()
{
	Matrix4 lookAt = Matrix4::GetLookAt(Position, _viewDirection, _up);

	Matrix4 m = _projection.Multiply(lookAt);

	return m;
}