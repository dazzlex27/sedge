/*
===========================================================================
IDGenerator.cpp

Implements IDGenerator
===========================================================================
*/

#include "IDGenerator.h"

using namespace sedge;

uint IDGenerator::currentID = 0;

uint IDGenerator::GetNewID()
{
	return currentID++;
}