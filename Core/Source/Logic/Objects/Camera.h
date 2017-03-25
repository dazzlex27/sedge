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
	namespace logic
	{
		class Camera : public Entity
		{
		private:
			float _fov;
			float _aspectRatio;
			float _near;
			float _far;
			math::Vector3 _viewDirection;

		public:
			Camera();
			~Camera();

			inline float GetFOV() const { return _fov; }
			inline float GetAspectRatio() const { return _aspectRatio; }
			inline const math::Vector3& GetLookAt() const { return _viewDirection; }
 
			void SetFOV(float fov);
			void SetNear(float near);
			void SetFar(float far);
			void SetAspectRatio(float aspectRatio);
			void SetViewDirection(const math::Vector3& viewDirection);
			void SetPosition(const math::Vector3& position);
			math::Matrix4 GetTransformation() const;

		private:
			void Update();
		};
	}
}