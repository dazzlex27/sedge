/*
===========================================================================
Camera.h

Defines a class for in-game cameras.
===========================================================================
*/

#pragma once
#include "../Source/Math/Vector3.h"
#include "Logic/Objects/Entity.h"

namespace s3dge
{
	struct Matrix4;

	class Camera : public Entity
	{
	protected:
		float Fov;
		float AspectRatio;
		float Near;
		float Far;
		Matrix4 ProjectionMatrix;
		Matrix4 ViewMatrix;
		Vector3 ViewDirection;
		Vector3 Up;

	public:
		inline float GetFOV() const { return Fov; }
		inline float GetAspectRatio() const { return AspectRatio; }
		inline float GetNear() const { return Near; }
		inline float GetFar() const { return Far; }
		inline const Vector3& GetViewDirection() const { return ViewDirection; }
		inline const Vector3& GetUp() const { return Up; }

		void SetFOV(float fov);
		void SetAspectRatio(float aspectRatio);
		void SetNear(float near);
		void SetFar(float far);
		void SetViewDirection(const Vector3& viewDirection);
		virtual void SetPosition(const Point3D& position) override;
		void SetUp(const Vector3& up);

		const Matrix4& GetProjection();
		const Matrix4& GetView();

		void Render() override;
		void Update() override;

	protected:
		Camera();
		Camera(float fov, float aspectRatio, float near, float far, const Vector3& viewDirection = Vector3(0, 0, -1), const Vector3& up = Vector3(0, 1, 0));
		virtual ~Camera();

	protected:
		virtual void UpdatePerspective();
		virtual void UpdateView();
	};
}