/*
===========================================================================
Camera.cpp

Implements the Camera class.
===========================================================================
*/

#include "Camera.h"
#include "Math/Matrix4.h"

using namespace s3dge;
using namespace math;

Camera::Camera()
	: _fov(45.0f),
	_aspectRatio(16.0f / 9.0f),
	_near(0.1f),
	_far(100.0f),
	_viewDirection(Vector3(0, 0, 1)),
	_up(Vector3(0, 1, 0))
{
	UpdatePerspective();
	UpdateView();
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
	UpdateView();
}

Camera::~Camera()
{
}

void Camera::UpdatePerspective()
{
	_projection = Matrix4::GetPerspective(_fov, _aspectRatio, _near, _far);
}

void Camera::UpdateView()
{
	_view = Matrix4::GetLookAt(Position, Position + _viewDirection, _up);
}

void Camera::SetPosition(const Point3D& position)
{
	Position = Vector3(position);
	UpdateView();
}

void Camera::SetViewDirection(const Vector3& viewDirection)
{
	_viewDirection = viewDirection;
	UpdateView();
}

void Camera::SetUp(const Vector3& up)
{
	_up = up;
	UpdateView();
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

Matrix4 Camera::GetProjection()
{
	return _projection;
}

Matrix4 Camera::GetView()
{
	return _view;
}