/*
===========================================================================
Camera.h

Defines a class for in-game cameras.
===========================================================================
*/

#pragma once

#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Entity.h"

namespace s3dge
{
	class Camera : public Entity
	{
	private:
		float _fov;
		float _aspectRatio;
		float _near;
		float _far;
		math::Matrix4 _projection;
		math::Vector3 _viewDirection;
		math::Vector3 _up;

	public:
		Camera();
		Camera(float fov, float aspectRatio, float near, float far, const math::Vector3& viewDirection = math::Vector3(0, 0, -1), const math::Vector3& up = math::Vector3(0, 1, 0));
		~Camera();

		inline float GetFOV() const { return _fov; }
		inline float GetAspectRatio() const { return _aspectRatio; }
		inline float GetNear() const { return _near; }
		inline float GetFar() const { return _far; }
		inline const math::Vector3& GetViewDirection() const { return _viewDirection; }
		inline const math::Vector3& GetUp() const { return _up; }

		void SetFOV(float fov);
		void SetAspectRatio(float aspectRatio);
		void SetNear(float near);
		void SetFar(float far);
		void SetViewDirection(const math::Vector3& viewDirection);
		virtual void SetPosition(const Point3D& position) override;
		math::Matrix4 GetWorldToViewMatrix();

		void Render() override;
		void Update() override;

	private:
		void UpdatePerspective();
	};
}