#include "Entity.h"

using namespace s3dge;

Entity::Entity()
{
	Position = Vector3(0, 0, 0);
	Scale = Vector3(1, 1, 1);
	Rotation = Vector4(0, 0, 0, 0);
	ModelMatrix = Matrix4::GetIdentity();
}

void Entity::SetPosition(const Vector3& position)
{
	Position = Vector3(position);
	UpdateModelMatrix();
}

void Entity::SetScale(const Vector3& scale)
{ 
	Scale = scale; 
	UpdateModelMatrix();
}

void Entity::SetRotation(const Vector3& rotation, const float angle)
{
	Rotation = Vector4(rotation.x, rotation.y, rotation.z, angle);
	UpdateModelMatrix();
}

void Entity::SetRenderable(Renderable*const renderable)
{
	_renderable = renderable;
}

void Entity::UpdateModelMatrix()
{
	Matrix4 translation = Matrix4::GetTranslation(Position);
	Matrix4 scale = Matrix4::GetScale(Scale);
	Matrix4 rotation = Matrix4::GetRotation(Vector3(Rotation.x, Rotation.y, Rotation.z), Rotation.w);

	ModelMatrix = rotation * translation * scale;
}