/*
===========================================================================
Camera.cpp

Implements the Camera class.
===========================================================================
*/

#include "Camera.h"

using namespace s3dge;
using namespace logic;

Camera::Camera()
{
	rotation = math::vec3f(0, 0, 0); 
	_fov = 45.0f;
	_aspectRatio = 16 / 9.0;
	_near = 0.1f;
	_far = 100.0f;
	_viewDirection = math::vec3f(0, 0, 0);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	projection = math::mat4::GetPerspective(_fov, _aspectRatio, _near, _far);
}

void Camera::SetPosition(math::vec3f position)
{
	// TODO
	Update();
}

void Camera::SetViewDirection(math::vec3f lookAt)
{
	_viewDirection = lookAt;
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

math::mat4 Camera::GetTransformation() const
{
	return math::mat4::GetIdentity();
}