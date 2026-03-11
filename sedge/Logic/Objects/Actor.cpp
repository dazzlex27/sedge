#include "Actor.h"
#include "Graphics/Renderables/Renderable.h"
#include "System/MemoryManagement.h"

using namespace sedge;

// Renderable will be deleted by the actor
Actor::Actor(Renderable*const renderable)
	: _renderable(renderable)
{
	_renderable->SetModelMatrix(ModelMatrix);
}

Actor::~Actor()
{
	SafeDelete(_renderable);
}

void Actor::Draw()
{
	_renderable->Draw();
}

void Actor::UpdateModelMatrix()
{
	Entity::UpdateModelMatrix();
	_renderable->SetModelMatrix(ModelMatrix);
}
