/*
===========================================================================
Group.cpp

Implements the Group class
===========================================================================
*/

#include "Group.h"
#include "Internal/DeleteMacros.h"

using namespace s3dge;
using namespace graphics;

Group::Group()
{
}

Group::~Group()
{
	for (auto item : _renderables)
		SafeDelete(item);
}

void Group::Add(Renderable2D* renderable)
{
	_renderables.push_back(renderable);
}

void Group::Submit(Renderer2D* renderer)
{
	for (auto item : _renderables)
		renderer->Submit(item);
}