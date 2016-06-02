/*
===========================================================================
BaseObject.cpp

Implements the BaseObject class.
===========================================================================
*/

#include "BaseObject.h"
#include "System/IDGenerator.h"

using namespace s3dge;

BaseObject::BaseObject()
{
	_id = IDGenerator::GetNewID();
}

BaseObject::~BaseObject()
{
}