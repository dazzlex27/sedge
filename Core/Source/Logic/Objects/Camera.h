/*
===========================================================================
Camera.h

Defines a class for in-game cameras.
===========================================================================
*/

#pragma once
#include "../Source/Math/Vector3.h"
#include "Entity.h"

namespace s3dge
{
	struct Matrix4;

	class Camera : public Entity
	{
	private:
		float _fov;
		float _aspectRatio;
		float _near;
		float _far;
		Matrix4 _projection;
		Matrix4 _view;
		Vector3 _viewDirection;
		Vector3 _up;

	public:
		Camera();
		Camera(float fov, float aspectRatio, float near, float far, const Vector3& viewDirection = Vector3(0, 0, -1), const Vector3& up = Vector3(0, 1, 0));
		~Camera();

		inline float GetFOV() const { return _fov; }
		inline float GetAspectRatio() const { return _aspectRatio; }
		inline float GetNear() const { return _near; }
		inline float GetFar() const { return _far; }
		inline const Vector3& GetViewDirection() const { return _viewDirection; }
		inline const Vector3& GetUp() const { return _up; }

		void SetFOV(float fov);
		void SetAspectRatio(float aspectRatio);
		void SetNear(float near);
		void SetFar(float far);
		void SetViewDirection(const Vector3& viewDirection);
		virtual void SetPosition(const Point3D& position) override;
		void SetUp(const Vector3& up);

		Matrix4 GetProjection();
		Matrix4 GetView();

		void Render() override;
		void Update() override;

	private:
		void UpdatePerspective();
		void UpdateView();
	};
}