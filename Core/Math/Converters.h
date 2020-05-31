/*
===========================================================================
Converters.h

Lists a few functions for mathematical conversions. Might be refactored later.
===========================================================================
*/

#pragma once

#include <CustomTypes.h>
#include "Math/Vector4.h"

namespace s3dge
{
	inline const float DegToRad(const float degrees)
	{
		return degrees * 3.14159265f / 180.0f;
	}

	inline const float RadToDeg(const float radians)
	{
		return radians / 3.14159265f * 180.0f;
	}
}