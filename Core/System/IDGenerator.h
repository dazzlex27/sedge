/*
===========================================================================
IDGenerator.h

A very primitive class for assigning IDs to objects.
===========================================================================
*/

#pragma once

#include <CustomTypes.h>

namespace sedge
{
	class IDGenerator
	{
	private:
		static uint currentID;

	public:
		static uint GetNewID();

	private:
		IDGenerator();
		IDGenerator(const IDGenerator& tRef) = delete;
		IDGenerator& operator = (const IDGenerator& tRef) = delete;
		~IDGenerator(void) {}
	};
}