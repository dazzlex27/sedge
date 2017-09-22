/*
===========================================================================
Camera.cpp

Implements the Camera class.
===========================================================================
*/

#include "Camera.h"

using namespace s3dge;

Camera::Camera()
	: Fov(45.0f),
	AspectRatio(16.0f / 9.0f),
	Near(0.1f),
	Far(100.0f),
	ViewDirection(Vector3(0, 0, -1)),
	Up(Vector3(0, 1, 0))
{
	UpdatePerspective();
	UpdateView();
}

Camera::Camera(const float fov, const float aspectRatio, const float near, const float far, const Vector3& viewDirection, const Vector3& up)
	: Fov(fov),
	AspectRatio(aspectRatio),
	Near(near),
	Far(far),
	ViewDirection(viewDirection),
	Up(up)
{
	UpdatePerspective();
	UpdateView();
}

Camera::~Camera()
{
}

void Camera::UpdatePerspective()
{
	ProjectionMatrix = Matrix4::GetPerspective(Fov, AspectRatio, Near, Far);
}

void Camera::UpdateView()
{
	ViewMatrix = Matrix4::LookAt(Position, Position + ViewDirection, Up);
}

void Camera::SetPosition(const Vector3& position)
{
	Position = position;
	UpdateView();
}

void Camera::SetViewDirection(const Vector3& viewDirection)
{
	ViewDirection = viewDirection;
	UpdateView();
}

void Camera::SetUp(const Vector3& up)
{
	Up = up;
	UpdateView();
}

void Camera::SetFOV(const float fov)
{
	Fov = fov;
	UpdatePerspective();
}

void Camera::SetAspectRatio(const float aspectRatio)
{
	AspectRatio = aspectRatio;
	UpdatePerspective();
}

void Camera::SetNear(const float near)
{
	Near = near;
	UpdatePerspective();
}

void Camera::SetFar(const float far)
{
	Far = far;
	UpdatePerspective();
}

const Matrix4& Camera::GetProjection()
{
	return ProjectionMatrix;
}

const Matrix4& Camera::GetView()
{
	return ViewMatrix;
}