/*
===========================================================================
Group.cpp

Implements the Group class
===========================================================================
*/

#include "Group.h"
#include "System/DeleteMacros.h"

using namespace s3dge;

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