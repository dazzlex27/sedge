#include "Entity.h"

using namespace s3dge;

Entity::Entity()
{
	Position = Vector3(0, 0, 0);
	Scale = Vector3(1, 1, 1);
	ModelMatrix = Matrix4::GetIdentity();
}

void Entity::SetPosition(const Point3D& position)
{
	Position = Vector3(position);
	UpdateModelMatrix();
}

void Entity::SetScale(const Vector3& scale)
{ 
	Scale = scale; 
	UpdateModelMatrix();
}

void Entity::SetRotation(const Vector3& rotation)
{
	Rotation = rotation;
	UpdateModelMatrix();
}

void Entity::SetRenderable(graphics::Renderable* renderable)
{
	_renderable = renderable;
}

void Entity::UpdateModelMatrix()
{
	Matrix4 translation = Matrix4::Translate(Position);
	Matrix4 scale = Matrix4::Scale(Scale);
	Matrix4 rotation = Matrix4::GetIdentity();

	ModelMatrix = translation * rotation * scale;
}