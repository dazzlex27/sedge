/*
===========================================================================
IDGenerator.cpp

Implements IDGenerator
===========================================================================
*/

#include "IDGenerator.h"

using namespace s3dge;

uint IDGenerator::currentID = 0;

uint IDGenerator::GetNewID()
{
	return currentID++;
}