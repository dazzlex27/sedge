/*
===========================================================================
BaseObject.h

A parent-class for all in-game objects. Takes responsibility of assigning IDs to created objects.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	class BaseObject
	{
	private:
		uint _id;

	public:
		BaseObject();
		virtual ~BaseObject();

		inline uint GetID() const { return _id; }
	};
}