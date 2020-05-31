/*
===========================================================================
Color.h

A structure to represent color across the engine's graphics subsystem.
Uses uint internally to store the actual RGB-color value.
===========================================================================
*/

#pragma once

#include <CustomTypes.h>
#include "Math/Vector4.h"

namespace s3dge
{
	struct Color
	{
		uint value;

		Color() : value(0) { }
		Color(uint value) : value(value) { }
		Color(const Vector4& color)
		{ 
			int red = (int)(color.x * 255);
			int green = (int)(color.y * 255);
			int blue = (int)(color.z * 255);
			int alpha = (int)(color.w * 255);

			value =  alpha << 24 | blue << 16 | green << 8 | red;
		}
		~Color() { }

		const Vector4& GetValueVec4() const 
		{ 
			Vector4 result;

			result.x = (float)(value >> 0);
			result.y = (float)(value >> 8);
			result.z = (float)(value >> 16);
			result.w = (float)(value >> 24);

			return result;
		}
	};
}