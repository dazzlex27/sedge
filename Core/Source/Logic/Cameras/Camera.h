/*
===========================================================================
Camera.h

Defines a class for in-game cameras.
===========================================================================
*/

#pragma once

#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Logic/Objects/BaseObject.h"

namespace s3dge
{
	struct Matrix4;

	class Camera : public BaseObject
	{
	protected:
		float Fov;
		float AspectRatio;
		float Near;
		float Far;
		Vector3 Position;
		Vector3 ViewDirection;
		Vector3 Up;
		Matrix4 ProjectionMatrix;
		Matrix4 ViewMatrix;

	public:
		inline float GetFOV() const { return Fov; }
		inline float GetAspectRatio() const { return AspectRatio; }
		inline float GetNear() const { return Near; }
		inline float GetFar() const { return Far; }
		inline const Vector3& GetPosition() const { return Position; }
		inline const Vector3& GetViewDirection() const { return ViewDirection; }
		inline const Vector3& GetUp() const { return Up; }

		void SetFOV(float fov);
		void SetAspectRatio(float aspectRatio);
		void SetNear(float near);
		void SetFar(float far);
		void SetViewDirection(const Vector3& viewDirection);
		virtual void SetPosition(const Point3D& position);
		void SetUp(const Vector3& up);

		const Matrix4& GetProjection();
		const Matrix4& GetView();

	protected:
		Camera();
		Camera(float fov, float aspectRatio, float near, float far, const Vector3& viewDirection = Vector3(0, 0, -1), const Vector3& up = Vector3(0, 1, 0));
		
	public:
		virtual ~Camera();

	protected:
		virtual void UpdatePerspective();
		virtual void UpdateView();
	};
}