#include "Actor.h"
#include "Graphics/Renderables/Renderable.h"

using namespace s3dge;

Actor::Actor(Renderable*const renderable)
{
	_renderable = renderable;
}

void Actor::Update()
{

}

void Actor::Draw()
{
	_renderable->Draw();
}