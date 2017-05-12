/*
===========================================================================
Entity.h

Represents a game entity.
===========================================================================
*/

#pragma once

#include "../Components/IComponent.h"
#include "BaseObject.h"
#include "Math/Point3D.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace s3dge
{
	namespace graphics
	{
		class Renderable;
	}

	class Entity : public BaseObject
	{
	protected:
		Vector3 Position;
		Vector3 Scale;
		Vector3 Rotation;
		Matrix4 ModelMatrix;

	private:
		graphics::Renderable* _renderable;

	public:
		Entity();
		~Entity() {}

	public:
		void AddComponent(IComponent* component)
		{

		}

		virtual void Update() = 0;
		virtual void Render() = 0;

		inline virtual const Vector3& GetPosition() const { return Position; }
		inline virtual const Vector3& GetScale() const { return Scale; }
		inline virtual const Vector3& GetRotation() const { return Rotation; }
		inline virtual const Matrix4& GetModelMatrix() const { return ModelMatrix; }
		inline virtual const graphics::Renderable* GetRenderable() const { return _renderable; }

		virtual void SetPosition(const Point3D& position);
		virtual void SetScale(const Vector3& scale);
		virtual void SetRotation(const Vector3& rotation);
		virtual void SetRenderable(graphics::Renderable* renderable);

	private:
		void UpdateModelMatrix();

		Entity(const Entity& tRef) = delete;				// Disable copy constructor.
		Entity& operator = (const Entity& tRef) = delete;	// Disable assignment operator.
	};
}