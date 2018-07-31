/*
===========================================================================
Entity.h

Represents a game entity.
===========================================================================
*/

#pragma once

#include "../Components/IComponent.h"
#include "BaseObject.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"

namespace s3dge
{
	class Renderable;
	struct Vector3;
	struct Matrix4;

	class Entity : public BaseObject
	{
	protected:
		Vector3 Position;
		Vector3 Scale;
		Vector4 Rotation;
		Matrix4 ModelMatrix;

	public:
		Entity();
		virtual ~Entity() {}

		virtual void Draw() = 0;

		inline virtual const Vector3& GetPosition() const { return Position; }
		inline virtual const Vector3& GetScale() const { return Scale; }
		inline virtual const Vector4& GetRotation() const { return Rotation; }
		inline virtual const Matrix4& GetModelMatrix() const { return ModelMatrix; }

		virtual void SetPosition(const Vector3& position);
		virtual void SetScale(const Vector3& scale);
		virtual void SetRotation(const Vector3& rotation, const float angle);

	protected:
		virtual void UpdateModelMatrix();

	private:
		Entity(const Entity& tRef) = delete;				// Disable copy constructor.
		Entity& operator = (const Entity& tRef) = delete;	// Disable assignment operator.
	};
}