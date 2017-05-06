/*
===========================================================================
Converters.h

Lists a few functions for mathematical conversions. Might be refactored later.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Math/Vector4.h"

namespace s3dge
{
	inline uint ConvertColorToUint(const Vector4& color)
	{
		int red = (int)(color.x * 255);
		int green = (int)(color.y * 255);
		int blue = (int)(color.z * 255);
		int alpha = (int)(color.w * 255);

		return alpha << 24 | blue << 16 | green << 8 | red;
	}

	inline Vector4 ConvertColorToVec4(uint color)
	{
		Vector4 result;

		result.x = (float)(color >> 0);
		result.y = (float)(color >> 8);
		result.z = (float)(color >> 16);
		result.w = (float)(color >> 24);
		
		return result;
	}

	inline float DegToRad(float degrees)
	{
		return degrees * 3.14159265f / 180.0f;
	}

	inline float RadToDeg(float radians)
	{
		return radians / 3.14159265f * 180.0f;
	}
}