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
		Point3D position;
		math::Matrix4 projection;
		math::Vector3 rotation;
		math::Vector3 scale;

	public:
		Entity() { scale = math::Vector3(1, 1, 1); }
		~Entity() {}

	public:
		void AddComponent(IComponent* component)
		{

		}

		virtual void Update() = 0;
		virtual void Render() = 0;

	private:
		Entity(const Entity& tRef) = delete;				// Disable copy constructor.
		Entity& operator = (const Entity& tRef) = delete;	// Disable assignment operator.
	};
}