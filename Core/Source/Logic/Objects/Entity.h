/*
===========================================================================
Entity.h

Represents a game entity.
===========================================================================
*/

#pragma once

#include "../Components/IComponent.h"
#include "BaseObject.h"
#include "Common/Structures/Point3D.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace s3dge
{
	class Entity : public BaseObject
	{
	protected:
		math::Vector3 Position;
		math::Vector3 Scale;
		math::Vector3 Rotation;

	public:
		Entity() 
		{
			Position = math::Vector3(0, 0, 0);
			Scale = math::Vector3(1, 1, 1); 
		}
		~Entity() {}

	public:
		void AddComponent(IComponent* component)
		{

		}

		virtual void Update() = 0;
		virtual void Render() = 0;

		inline Point3D GetPosition() const { return Position; }

		virtual void SetPosition(const Point3D& position) { Position = math::Vector3(position); }
		virtual void SetScale(const math::Vector3& scale) { Scale = scale; }

	private:
		Entity(const Entity& tRef) = delete;				// Disable copy constructor.
		Entity& operator = (const Entity& tRef) = delete;	// Disable assignment operator.
	};
}